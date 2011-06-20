#ifdef ARCH_ia32 // TODO need PCI flag instead
/**
 *
 * Phantom OS
 *
 * Copyright (C) 2005-2011 Dmitry Zavalishin, dz@dz.ru
 *
 * IDE AHCI driver.
 *
**/
#define DEV_NAME "ahci"
#define DEBUG_MSG_PREFIX "ahci"
#include <debug_ext.h>
#define debug_level_flow 9
#define debug_level_error 10
#define debug_level_info 10

#include <kernel/drivers.h>
#include <kernel/page.h>
#include <kernel/atomic.h>
#include <kernel/libkern.h>

#include <i386/pio.h>
#include <errno.h>
#include <assert.h>
#include <hal.h>
#include <time.h>
#include <disk.h>

#include <pager_io_req.h>

#include <dev/pci/ahci.h>

#define ATA_CMD_IDENT	0xEC	/* Identify Device		*/

#define ATA_CMD_RD_DMA	0xC8	/* Read DMA (with retries)	*/
#define ATA_CMD_RD_DMAN	0xC9	/* Read DMS ( no  retries)	*/
#define ATA_CMD_WR_DMA	0xCA	/* Write DMA (with retries)	*/
#define ATA_CMD_WR_DMAN	0xCB	/* Write DMA ( no  retires)	*/
/*
 * structure returned by ATA_CMD_IDENT, as per ANSI ATA2 rev.2f spec
 */
typedef struct hd_driveid {
    unsigned short	config;		/* lots of obsolete bit flags */
    unsigned short	cyls;		/* "physical" cyls */
    unsigned short	reserved2;	/* reserved (word 2) */
    unsigned short	heads;		/* "physical" heads */
    unsigned short	track_bytes;	/* unformatted bytes per track */
    unsigned short	sector_bytes;	/* unformatted bytes per sector */
    unsigned short	sectors;	/* "physical" sectors per track */
    unsigned short	vendor0;	/* vendor unique */
    unsigned short	vendor1;	/* vendor unique */
    unsigned short	vendor2;	/* vendor unique */
    unsigned char	serial_no[20];	/* 0 = not_specified */
    unsigned short	buf_type;
    unsigned short	buf_size;	/* 512 byte increments; 0 = not_specified */
    unsigned short	ecc_bytes;	/* for r/w long cmds; 0 = not_specified */
    unsigned char	fw_rev[8];	/* 0 = not_specified */
    unsigned char	model[40];	/* 0 = not_specified */
    unsigned char	max_multsect;	/* 0=not_implemented */
    unsigned char	vendor3;	/* vendor unique */
    unsigned short	dword_io;	/* 0=not_implemented; 1=implemented */
    unsigned char	vendor4;	/* vendor unique */
    unsigned char	capability;	/* bits 0:DMA 1:LBA 2:IORDYsw 3:IORDYsup*/
    unsigned short	reserved50;	/* reserved (word 50) */
    unsigned char	vendor5;	/* vendor unique */
    unsigned char	tPIO;		/* 0=slow, 1=medium, 2=fast */
    unsigned char	vendor6;	/* vendor unique */
    unsigned char	tDMA;		/* 0=slow, 1=medium, 2=fast */
    unsigned short	field_valid;	/* bits 0:cur_ok 1:eide_ok */
    unsigned short	cur_cyls;	/* logical cylinders */
    unsigned short	cur_heads;	/* logical heads */
    unsigned short	cur_sectors;	/* logical sectors per track */
    unsigned short	cur_capacity0;	/* logical total sectors on drive */
    unsigned short	cur_capacity1;	/*  (2 words, misaligned int)     */
    unsigned char	multsect;	/* current multiple sector count */
    unsigned char	multsect_valid;	/* when (bit0==1) multsect is ok */
    unsigned int	lba_capacity;	/* total number of sectors */
    unsigned short	dma_1word;	/* single-word dma info */
    unsigned short	dma_mword;	/* multiple-word dma info */
    unsigned short  eide_pio_modes; /* bits 0:mode3 1:mode4 */
    unsigned short  eide_dma_min;	/* min mword dma cycle time (ns) */
    unsigned short  eide_dma_time;	/* recommended mword dma cycle time (ns) */
    unsigned short  eide_pio;       /* min cycle time (ns), no IORDY  */
    unsigned short  eide_pio_iordy; /* min cycle time (ns), with IORDY */
    unsigned short	words69_70[2];	/* reserved words 69-70 */
    unsigned short	words71_74[4];	/* reserved words 71-74 */
    unsigned short  queue_depth;	/*  */
    unsigned short  words76_79[4];	/* reserved words 76-79 */
    unsigned short  major_rev_num;	/*  */
    unsigned short  minor_rev_num;	/*  */
    unsigned short  command_set_1;	/* bits 0:Smart 1:Security 2:Removable 3:PM */
    unsigned short	command_set_2;	/* bits 14:Smart Enabled 13:0 zero 10:lba48 support*/
    unsigned short  cfsse;		/* command set-feature supported extensions */
    unsigned short  cfs_enable_1;	/* command set-feature enabled */
    unsigned short  cfs_enable_2;	/* command set-feature enabled */
    unsigned short  csf_default;	/* command set-feature default */
    unsigned short  	dma_ultra;	/*  */
    unsigned short	word89;		/* reserved (word 89) */
    unsigned short	word90;		/* reserved (word 90) */
    unsigned short	CurAPMvalues;	/* current APM values */
    unsigned short	word92;		/* reserved (word 92) */
    unsigned short	hw_config;	/* hardware config */
    unsigned short	words94_99[6];/* reserved words 94-99 */
    /*unsigned long long  lba48_capacity; /--* 4 16bit values containing lba 48 total number of sectors */
    unsigned short	lba48_capacity[4]; /* 4 16bit values containing lba 48 total number of sectors */
    unsigned short	words104_125[22];/* reserved words 104-125 */
    unsigned short	last_lun;	/* reserved (word 126) */
    unsigned short	word127;	/* reserved (word 127) */
    unsigned short	dlf;		/* device lock function
    * 15:9	reserved
    * 8	security level 1:max 0:high
    * 7:6	reserved
    * 5	enhanced erase
    * 4	expire
    * 3	frozen
    * 2	locked
    * 1	en/disabled
    * 0	capability
    */
    unsigned short  csfo;		/* current set features options
    * 15:4	reserved
    * 3	auto reassign
    * 2	reverting
    * 1	read-look-ahead
    * 0	write cache
    */
    unsigned short	words130_155[26];/* reserved vendor words 130-155 */
    unsigned short	word156;
    unsigned short	words157_159[3];/* reserved vendor words 157-159 */
    unsigned short	words160_162[3];/* reserved words 160-162 */
    unsigned short	cf_advanced_caps;
    unsigned short	words164_255[92];/* reserved words 164-255 */
} hd_driveid_t;




typedef struct
{
    phantom_device_t *		dev;            // disk io needs it
    int                         nport;

    int                 	exist;
    u_int32_t                   nSect;

    u_int32_t                   c_started; // which commands are started - to compare with running list

    physaddr_t          	clb_p;
    struct ahci_cmd_list*	clb;

    physaddr_t          	fis_p;
    void *              	fis;

    struct ahci_cmd_tab *       cmds;

    pager_io_request *          reqs[AHCI_CL_SIZE];
} ahci_port_t;


typedef struct
{
    int                 ncs;
    ahci_port_t         port[32];
} ahci_t;

static void ahci_interrupt(void *arg);

static int ahci_init(phantom_device_t *dev);

//static int ahci_start(phantom_device_t *dev);
//static int ahci_stop(phantom_device_t *dev);

static int ahci_write(phantom_device_t *dev, const void *buf, int len);
static int ahci_read(phantom_device_t *dev, void *buf, int len);

//static int ahci_ioctl(struct phantom_device *dev, int type, void *buf, int len);


static void ahci_process_finished_cmd(phantom_device_t *dev, int nport);

static errno_t ahci_do_inquiry(phantom_device_t *dev, int nport, void *data, size_t data_len );


static void dump_ataid(hd_driveid_t *ataid);
//static void ahci_dump_port_info(phantom_device_t *dev, int nport );

static void ahci_connect_port( ahci_port_t *p );



static int seq_number = 0;
phantom_device_t * driver_ahci_probe( pci_cfg_t *pci, int stage )
{

    (void) stage;

    SHOW_FLOW( 1, "Probe for " DEV_NAME " stage %d", stage );

    phantom_device_t * dev = malloc(sizeof(phantom_device_t));

    int i;
    for (i = 0; i < 6; i++)
    {
        if (pci->base[i] > 0xffff)
        {
            dev->iomem = (pci->base[i]);
            dev->iomemsize = pci->size[i];
            SHOW_INFO( 1, "mem base 0x%lx, size 0x%lx", dev->iomem, dev->iomemsize);
        } else if( pci->base[i] > 0) {
            dev->iobase = pci->base[i];
            SHOW_INFO( 1, "io_port 0x%x", dev->iobase);
        }
    }

    dev->irq = pci->interrupt;


    const int n_pages = BYTES_TO_PAGES(dev->iomemsize);
    void *va;
    if( hal_alloc_vaddress(&va,n_pages ) )
        panic("Can't alloc vaddress for %d mem pages", n_pages);

    hal_pages_control_etc( dev->iomem, va, n_pages, page_map_io, page_rw, 0 );

    dev->iomem = (addr_t)va; // loose phys addr?!

    /*
    // Gets port 0. uninited by BIOS? Need explicit PCI io addr assign?
    if( dev->iobase == 0 )
    {
        SHOW_ERROR0( 0, "No io port?" );
        goto free;
    }
    */

    SHOW_FLOW( 1, "Look for " DEV_NAME " at mem %X", dev->iomem );
    //if( check_ahci_sanity(dev->iobase) )        goto free;

    dev->name = DEV_NAME;
    dev->seq_number = seq_number++;

    //dev->dops.start = ahci_start;
    //dev->dops.stop  = ahci_stop;
    dev->dops.read  = ahci_read;
    dev->dops.write = ahci_write;
    //dev->dops.ioctl = ahci_ioctl;

    if( hal_irq_alloc( dev->irq, &ahci_interrupt, dev, HAL_IRQ_SHAREABLE ) )
    {
        SHOW_ERROR( 0, "IRQ %d is busy", dev->irq );
        goto free;
    }

    ahci_t *es = calloc(1,sizeof(ahci_t));
    assert(es);
    dev->drv_private = es;

    if( ahci_init(dev) )
        goto free1;

    return dev;
free1:
    free(es);

free:
    free(dev);
    return 0;
}


static inline addr_t ahci_port_base( phantom_device_t *dev, int port)
{
    return dev->iomem + 0x100 + (port * 0x80);
}

static inline u_int32_t RP32( phantom_device_t *dev, int port, int displ)
{
    return *(u_int32_t*) (ahci_port_base(dev,port)+displ);
}

static inline void WP32( phantom_device_t *dev, int port, int displ, u_int32_t v)
{
    *(u_int32_t*) (ahci_port_base(dev,port)+displ) = v;
}


#define W32(__d,__p,__v) ( *((u_int32_t*)(__d->iomem+(__p))) ) = __v
#define R32(__d,__p) ( *((u_int32_t*)( ((int)(__d)->iomem) + (int)(__p))) )


static errno_t ahci_init_port(phantom_device_t *dev, int nport)
{
    ahci_t *a = dev->drv_private;

    SHOW_FLOW( 1, "Init " DEV_NAME " at mem %X, port %d", dev->iomem, nport );

    ahci_port_t *p = a->port+nport;

    p->dev = dev;
    p->nport = nport;

    // TODO 64bit -- NEED some define that we support 64 bit on this arch

    hal_pv_alloc( &(p->clb_p), (void**)&(p->clb), 1024 );
    WP32( dev, nport, AHCI_P_CLB, p->clb_p );
    //WP32( dev, nport, AHCI_P_CLBU, p->clb_p >> 32 );
    memset( p->clb, 1024, 0 );

    hal_pv_alloc( &(p->fis_p), (void**)&(p->fis), 4096 );
    WP32( dev, nport, AHCI_P_FB, p->fis_p );
    //WP32( dev, nport, AHCI_P_FBU, p->fis_p >> 32 );
    memset( p->fis, 4096, 0 );

    // We allocate 32 commands at once and fill phys addresses right now

    const unsigned int cmd_bytes = 0x100;
    assert(cmd_bytes >= sizeof(struct ahci_cmd_tab));

    physaddr_t pa;
    void *va;
    hal_pv_alloc( &(pa), &va, cmd_bytes*AHCI_CL_SIZE );
    memset( va, cmd_bytes*AHCI_CL_SIZE, 0 );

    p->cmds = va;

    int i;
    for( i = 0; i < AHCI_CL_SIZE; i++ )
    {
        p->clb[i].cmd_table_phys = pa + (i*cmd_bytes);
    }

    WP32( dev, nport, AHCI_P_IE, 0xFFFF ); // Turn on all...

    WP32( dev, nport, AHCI_P_CMD, AHCI_P_CMD_FRE|AHCI_P_CMD_SUD|AHCI_P_CMD_POD );
    WP32( dev, nport, AHCI_P_CMD, AHCI_P_CMD_FRE|AHCI_P_CMD_SUD|AHCI_P_CMD_ST|AHCI_P_CMD_ACTIVE|AHCI_P_CMD_POD );

    //ahci_dump_port_info( dev, nport );

    {
    hd_driveid_t id;

    errno_t rc = ahci_do_inquiry( dev, nport, &id, sizeof(id) );
    if(rc)
    {
        SHOW_ERROR( 0, "ahci_do_inquiry rc = %d", rc );
        return rc;
    }

    p->nSect = id.lba_capacity;

    dump_ataid( &id );

    ahci_connect_port( p );

    }


    return 0;
}


static int ahci_init(phantom_device_t *dev)
{
    ahci_t *a = dev->drv_private;

    SHOW_FLOW( 1, "Init " DEV_NAME " at mem %X", dev->iomem );
    //SHOW_FLOW( 1, "read reg at mem %X", dev->iomem+AHCI_CAP );

    u_int32_t r = R32(dev,AHCI_GHC);
    if( ! (r & AHCI_GHC_AE ) )
    {
        SHOW_INFO( 1, "AHI ENABLE for " DEV_NAME " is off (%X)", r );

        W32(dev,AHCI_GHC, r | AHCI_GHC_AE );

        r = R32(dev,AHCI_GHC);
        if( ! (r & AHCI_GHC_AE ) )
        {
            SHOW_ERROR( 1, "Unable to ENABLE " DEV_NAME " (%X)", r );
            return ENXIO;
        }

        W32(dev,AHCI_GHC, r | AHCI_GHC_HR ); // Reset
        W32(dev,AHCI_GHC, r | AHCI_GHC_IE ); // Enable interrupts

    }

    // TODO bios ownership?

    u_int32_t cap = R32(dev,AHCI_CAP);
    //u_int32_t cap = *(u_int32_t *)(dev->iomem+AHCI_CAP);

    int nports = 1 + (cap & AHCI_CAP_NPMASK);
    a->ncs = 1 + ((cap & AHCI_CAP_NCS) >> AHCI_CAP_NCS_SHIFT);

    SHOW_INFO(0,"ports %d, cs %d", nports, a->ncs );

    u_int32_t ports = R32(dev,AHCI_PI);

    //SHOW_FLOW( 1, " " DEV_NAME ", ports %X", ports );

    int nport = 0;
    while(ports)
    {
        if( ports & 1 )
        {
            a->port[nport].exist = 1;
            SHOW_INFO( 4, "port %d implemented", nport );
            if( ahci_init_port(dev, nport) )
                return ENXIO;
        }
        ports <<= 1;
        nport++;
    }

    // now tell us something

    printf("AHCI flags: %s%s%s%s%s%s%s%s%s%s%s%s%s\n",
           cap & (1 << 31) ? "64bit " : "",
           cap & (1 << 30) ? "ncq " : "",
           cap & (1 << 28) ? "ilck " : "",
           cap & (1 << 27) ? "stag " : "",
           cap & (1 << 26) ? "pm " : "",
           cap & (1 << 25) ? "led " : "",
           cap & (1 << 24) ? "clo " : "",
           cap & (1 << 19) ? "nz " : "",
           cap & (1 << 18) ? "only " : "",
           cap & (1 << 17) ? "pmp " : "",
           cap & (1 << 15) ? "pio " : "",
           cap & (1 << 14) ? "slum " : "",
	       cap & (1 << 13) ? "part " : "");

    return 0;
}

static void ahci_port_interrupt(phantom_device_t *dev, int nport)
{
    ahci_t *a = dev->drv_private;

    u_int32_t is = RP32( dev, nport, AHCI_P_IS );
    WP32( dev, nport, AHCI_P_IS, is );

    if( !a->port[nport].exist )
    {
        SHOW_ERROR( 1, "Interrupt from nonexisting port %d, is %X", nport, is );
        WP32( dev, nport, AHCI_P_IE, 0 ); // Turn off!
        return;
    }

    SHOW_FLOW( 1, "Interrupt from port %d, is %X", nport, is );

    ahci_process_finished_cmd(dev, nport);
}


static void ahci_interrupt(void *arg)
{
    phantom_device_t *dev = arg;

    u_int32_t ports = R32(dev,AHCI_IS);
    u_int32_t ports_copy = ports;

    SHOW_FLOW( 1, "Interrupt from " DEV_NAME ", ports %X", ports );

    int nport = 0;
    while(ports)
    {
        if( ports & 1 )
            ahci_port_interrupt(dev, nport);
        ports <<= 1;
        nport++;
    }

    W32(dev,AHCI_IS, ports_copy );

}

static void ahci_wait_for_port_interrupt(phantom_device_t *dev, int nport)
{
    (void) dev;
    (void) nport;

    // XXX BUG TODO
    hal_sleep_msec(1);
}


static int ahci_find_free_cmd(phantom_device_t *dev, int nport)
{
    ahci_t *a = dev->drv_private;

    while(1)
    {
        u_int32_t slots = RP32(dev, nport, AHCI_P_CI);

        slots &= RP32(dev, nport, AHCI_P_SACT );

        slots |= a->port[nport].c_started;

        int slot = ffr(slots);
        if( slot == 0 )
            ahci_wait_for_port_interrupt(dev, nport);

        SHOW_FLOW( 8, "found slot %d on port %d ", slot-1, nport );
        return slot - 1; // 0 = none
    }

}



static void ahci_start_cmd(phantom_device_t *dev, int nport, int ncmd)
{
    ahci_t *a = dev->drv_private;
    WP32( dev, nport, AHCI_P_CI, 1 >> ncmd);
    atomic_or( (int *)&(a->port[nport].c_started), 1 >> ncmd );
}


static void ahci_wait_cmd(phantom_device_t *dev, int nport, int ncmd)
{
    //ahci_t *a = dev->drv_private;

    while( RP32( dev, nport, AHCI_P_CI ) & (1 >> ncmd) )
    {
        hal_sleep_msec( 1 );
    }
}


// returns cmd index
static int ahci_build_req_cmd(phantom_device_t *dev, int nport, pager_io_request *req )
{
    ahci_t *a = dev->drv_private;

    int pFreeSlot = ahci_find_free_cmd( dev, nport );

    assert(pFreeSlot<AHCI_CL_SIZE);

    struct ahci_cmd_tab *       cmd = a->port[nport].cmds+pFreeSlot;
    struct ahci_cmd_list*	cp = a->port[nport].clb+pFreeSlot;

    a->port[nport].reqs[pFreeSlot] = req;

    SHOW_FLOW( 9, "rq sect %d", req->blockNo );

    cp->prd_length = 1;
    cp->cmd_flags = ( (req->flag_pageout) ? AHCI_CMD_WRITE : 0);
    cp->bytecount = 0;

    // TODO assert req->nSect * 512 < max size per prd

    cmd->prd_tab[0].dba = req->phys_page;
    cmd->prd_tab[0].dbc = req->nSect * 512;

    u_int8_t fis[20];

    /* Construct the FIS */
    fis[0] = 0x27;		/* Host to device FIS. */
    fis[1] = 1 << 7;	        /* Command FIS. */
    fis[2] = (req->flag_pageout) ? ATA_CMD_WR_DMA : ATA_CMD_RD_DMA;	/* Command byte. */

    u_int32_t lba = req->blockNo;

    /* LBA address, only support LBA28 in this driver */
    fis[4] = lba;
    fis[5] = lba >> 8;
    fis[6] = lba >> 16;
    fis[7] = ( (lba >> 24) & 0x0f) | 0xe0;

    u_int32_t nSect = req->nSect;

    assert( 0 == (nSect & 0xFFFF0000) );
    /* Sector Count */
    fis[12] = nSect;
    fis[13] = nSect >> 8;

    memcpy( cmd->cfis, fis, umin( sizeof(cmd->cfis), sizeof(fis) ) );

    unsigned fl = 16;
    cp->cmd_flags |= fl>>2;

    return pFreeSlot;
}


// returns cmd index
static int ahci_build_fis_cmd(phantom_device_t *dev, int nport, void *fis, size_t fis_len, physaddr_t data, size_t data_len, int isWrite )
{
    ahci_t *a = dev->drv_private;

    int pFreeSlot = ahci_find_free_cmd( dev, nport );

    assert(pFreeSlot<AHCI_CL_SIZE);

    struct ahci_cmd_tab *       cmd = a->port[nport].cmds+pFreeSlot;
    struct ahci_cmd_list*	cp = a->port[nport].clb+pFreeSlot;

    a->port[nport].reqs[pFreeSlot] = 0;

    cp->prd_length = 1;
    cp->cmd_flags = ( isWrite ? AHCI_CMD_WRITE : 0);
    cp->bytecount = 0;

    cp->cmd_flags |= fis_len >> 2;

    // TODO assert data_len < max size per prd

    memcpy( cmd->cfis, fis, umin( sizeof(cmd->cfis), fis_len ) );

    cmd->prd_tab[0].dba = data;
    cmd->prd_tab[0].dbc = data_len;

    return pFreeSlot;
}


static void ahci_finish_cmd(phantom_device_t *dev, int nport, int slot)
{
    ahci_t *a = dev->drv_private;
    //ahci_port_t *p = a->port+nport;

    //struct ahci_cmd_tab *       cmd = a->port[nport].cmds+slot;
    struct ahci_cmd_list*	cp = a->port[nport].clb+slot;
    pager_io_request *          req = a->port[nport].reqs[slot];

    // Now do it

    req->rc = 0;

    // TODO check error!

    if( cp->bytecount != ((unsigned) (req->nSect * 512)) )
    {
        req->rc = EIO;
        req->flag_ioerror = 1;
    }

    if(req) pager_io_request_done( req );
}


static void ahci_process_finished_cmd(phantom_device_t *dev, int nport)
{
    ahci_t *a = dev->drv_private;

    while(a->port[nport].c_started)
    {
        // TODO in splinlock to prevent races?

        u_int32_t slots = RP32( dev, nport, AHCI_P_CI );
        u_int32_t done = a->port[nport].c_started & ~slots;

        if( done == 0 )
            return;

        int slot = ffr(slots);
        if( slot == 0 )
            return;

        slot--; // 0 = none

        SHOW_FLOW( 8, "found completed slot %d on port %d ", slot, nport );


        ahci_finish_cmd( dev, nport, slot );

        // eat it
        atomic_and( (int *)&(a->port[nport].c_started), ~(1 >> slot) );
    }

}



static errno_t ahci_sync_read(phantom_device_t *dev, int nport, void *fis, size_t fis_len, void *data, size_t data_len )
{
    errno_t rc = 0;

    physaddr_t pa;
    void *va;
    hal_pv_alloc( &pa, &va, data_len );
    //va = calloc( data_len, 1 );    pa = va;

    SHOW_FLOW( 7, "pa %p va %p", pa, va );

    int slot = ahci_build_fis_cmd( dev, nport, fis, fis_len, pa, data_len, 0 );
    ahci_start_cmd( dev, nport, slot );
    ahci_wait_cmd( dev, nport, slot );

    memcpy( data, va, data_len );
    hal_pv_free( pa, va, data_len );

    ahci_t *a = dev->drv_private;
    struct ahci_cmd_list*	cp = a->port[nport].clb+slot;

    // check error

    if( cp->bytecount != data_len )
        rc = EIO;

    return rc;
}


/* SCSI INQUIRY */

static errno_t ahci_do_inquiry(phantom_device_t *dev, int nport, void *data, size_t data_len )
{
    u_int8_t fis[20];

    /* Construct the FIS */
    fis[0] = 0x27;		/* Host to device FIS. */
    fis[1] = 1 << 7;	/* Command FIS. */
    fis[2] = ATA_CMD_IDENT;	/* Command byte. */

    errno_t rc = ahci_sync_read( dev, nport, fis, sizeof(fis), data, data_len );

    //if( rc )
    return rc;
}








static int ahci_read(phantom_device_t *dev, void *buf, int len)
{
    (void) dev;
    (void) buf;
    (void) len;

    //ahci_t *es = dev->drv_private;

    return -1;
}

static int ahci_write(phantom_device_t *dev, const void *buf, int len)
{
    (void) dev;
    (void) buf;
    (void) len;

    //ahci_t *es = dev->drv_private;

    return -1;
}





//---------------------------------------------------------------------------
// Debug
//---------------------------------------------------------------------------





static void dump_ataid(hd_driveid_t *ataid)
{
    SHOW_INFO( 0, "lba_capacity = %d Kb", ataid->lba_capacity/2 );

    SHOW_INFO( 0, "(49) capability 	= 0x%x", ataid->capability);
    SHOW_INFO( 0, "(53) field_valid 	= 0x%x", ataid->field_valid);
    SHOW_INFO( 0, "(63) dma_mword 	= 0x%x", ataid->dma_mword);
    SHOW_INFO( 0, "(64) eide_pio_modes 	= 0x%x", ataid->eide_pio_modes);
    SHOW_INFO( 0, "(75) queue_depth 	= 0x%x", ataid->queue_depth);
    SHOW_INFO( 0, "(80) major_rev_num 	= 0x%x", ataid->major_rev_num);
    SHOW_INFO( 0, "(81) minor_rev_num 	= 0x%x", ataid->minor_rev_num);
    SHOW_INFO( 0, "(82) command_set_1 	= 0x%x", ataid->command_set_1);
    SHOW_INFO( 0, "(83) command_set_2 	= 0x%x", ataid->command_set_2);
    SHOW_INFO( 0, "(84) cfsse 		= 0x%x", ataid->cfsse);
    SHOW_INFO( 0, "(85) cfs_enable_1 	= 0x%x", ataid->cfs_enable_1);
    SHOW_INFO( 0, "(86) cfs_enable_2 	= 0x%x", ataid->cfs_enable_2);
    SHOW_INFO( 0, "(87) csf_default 	= 0x%x", ataid->csf_default);
    SHOW_INFO( 0, "(88) dma_ultra 	= 0x%x", ataid->dma_ultra);
    SHOW_INFO( 0, "(93) hw_config 	= 0x%x", ataid->hw_config);
}


//---------------------------------------------------------------------------
// Disk io interface
//---------------------------------------------------------------------------

// TODO specific must contain port, not dev! and need dev ptr in port



static errno_t ahci_AsyncIo( struct phantom_disk_partition *part, pager_io_request *rq )
{
    ahci_port_t *p = part->specific;
    phantom_device_t *dev = p->dev;

    rq->flag_ioerror = 0;
    rq->rc = 0;

    int slot = ahci_build_req_cmd(dev, p->nport, rq );
    ahci_start_cmd( dev, p->nport, slot );

    return 0;
}

phantom_disk_partition_t *phantom_create_ahci_partition_struct( ahci_port_t *p, long size )
{
    //phantom_device_t *dev = p->dev;

    phantom_disk_partition_t * ret = phantom_create_partition_struct( 0, 0, size );

    ret->asyncIo = ahci_AsyncIo;
    ret->flags |= PART_FLAG_IS_WHOLE_DISK;


    //struct disk_q *q = calloc( 1, sizeof(struct disk_q) );
    //phantom_init_disk_q( q, startIoFunc );

    ret->specific = p;
    strlcpy( ret->name, "AHCI0", sizeof(ret->name) );


    //q->device = private;
    //q->unit = unit; // if this is multi-unit device, let 'em distinguish

    // errno_t phantom_register_disk_drive(ret);

    return ret;
}


static void ahci_connect_port( ahci_port_t *p )
{

    int size = p->nSect;

    if(size <= 0)
    {
        SHOW_ERROR( 0, "Disk %d size %d?", p->nport, size );
        return;
    }

    phantom_disk_partition_t *part = phantom_create_ahci_partition_struct( p, size );
    if(part == 0)
    {
        SHOW_ERROR0( 0, "Failed to create whole disk partition" );
        return;
    }
// hangs
#if 0
    errno_t err = phantom_register_disk_drive(part);
    if(err)
    {
        SHOW_ERROR( 0, "Disk %d err %d", p->nport, err );
        return;
    }
#endif
}






#endif // ARCH_ia32









