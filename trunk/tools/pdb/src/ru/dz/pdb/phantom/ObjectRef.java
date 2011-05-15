package ru.dz.pdb.phantom;

import java.nio.ByteBuffer;

import ru.dz.pdb.Main;



/**
 * struct pvm_object
 * {
 *     struct pvm_object_storage	* data;
 *     struct pvm_object_storage	* interface; // method list is here
 * };
 * 
 * @author dz
 *
 */
public class ObjectRef {
	private long dataAddr;
	private long interfaceAddr;

	/**
	 * 
	 * @param bb buffer to load from
	 * @param pos start position of object
	 */
	public ObjectRef(ByteBuffer bb, int pos) {
		bb.position(pos);
		
		dataAddr = bb.getInt();
		interfaceAddr = bb.getInt();		
	}

	/**
	 * 
	 * @param bb buffer to load from
	 */
	public ObjectRef(ByteBuffer bb) {
		dataAddr = bb.getInt();
		interfaceAddr = bb.getInt();		
	}

	public ObjectRef(int dataAddr, int ifAddr ) {
		this.dataAddr = dataAddr;
		this.interfaceAddr = ifAddr;		
	}

	
	public long getDataAddr()      {		return dataAddr;	}
	public long getInterfaceAddr() {		return interfaceAddr;	}

	public ObjectHeader getObject() { return Main.getPhantomObject(dataAddr); }
}
