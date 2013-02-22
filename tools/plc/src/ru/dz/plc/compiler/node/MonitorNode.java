
package ru.dz.plc.compiler.node;

import java.io.IOException;

import ru.dz.phantom.code.Codegen;
import ru.dz.plc.compiler.CodeGeneratorState;
import ru.dz.plc.compiler.ParseState;
import ru.dz.plc.compiler.PhantomType;
import ru.dz.plc.util.PlcException;

 /**
 * Monitor lock/unlock
 */

public class MonitorNode extends Node {
	private boolean lock = false;
	//private PhantomClass my_class;


	public MonitorNode( Node value, boolean lock ) {
		super(value);
		this.lock =  lock;
	}
	public String toString()  {    return "monitor  "+ (lock ? "lock" : "unlock");  }
	public void find_out_my_type() throws PlcException { /* don't care */ type = PhantomType.getVoid(); }
	public boolean is_const() { return false; }

	
	@Override
	public boolean is_on_int_stack() {
		return false;
	}
	
	public void preprocess_me( ParseState s ) throws PlcException {
	}

	protected void generate_my_code(Codegen c, CodeGeneratorState s) throws IOException,
	PlcException {
		
		// Parameter - value
		_l.generate_code(c, s);
		move_between_stacks(c, _l.is_on_int_stack()); 
		
		if(lock) c.emitLock();		
		else     c.emitUnLock();
	}

}
