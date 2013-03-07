package ru.dz.plc.compiler;

import java.util.*;

import ru.dz.phantom.code.*;
import ru.dz.plc.compiler.node.Node;
import ru.dz.plc.util.PlcException;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

/**
 * <p>Represents a method.</p>
 * <p>Copyright: Copyright (c) 2004-2009 Dmitry Zavalishin</p>
 * <p>Company: <a href="http://dz.ru/en">Digital Zone</a></p>
 * @author dz
 */

public class Method
{
	private int         ordinal;
	public Node         code;
	public String       name;
	public PhantomType  type;
	public LinkedList<ArgDefinition>   args_def = new LinkedList<ArgDefinition>();

	private boolean requestDebug= false;

	// Main ones - on object stack
	public PhantomStack     svars = new PhantomStack();
	// Binary ones - on integer stack
	public PhantomStack     isvars = new PhantomStack();


	private Codegen c = new Codegen();



	public Method( String name, PhantomType type )
	{
		this.name = name;
		this.type = type;
		//this.args = null;
		this.ordinal = -1;
		this.code = null;
	}

	/** NB! Must be called in correct order! */
	public void addArg( String name, PhantomType type ) throws PlcException
	{
		if( type == null )
		{
			//Object a = null;        a.getClass();
			throw new PlcException("Method add_arg", "null type of arg", name);
		}

		args_def.add(new ArgDefinition(name, type));
		svars.add_stack_var( new PhantomVariable(name, type ) );
	}

	public String toString()
	{
		StringBuffer sb = new StringBuffer();

		sb.append( type.toString() );
		sb.append( " " );
		sb.append( name );
		sb.append( "( " );
		boolean first = true;
		for( Iterator<ArgDefinition> i = args_def.iterator(); i.hasNext(); )
		{
			if( !first ) sb.append(", ");
			first = false;
			sb.append(i.next().toString());
		}
		sb.append( " )" );

		return sb.toString();
	}

	public Codegen get_cg() { return c; }

	public void generate_code( CodeGeneratorState s ) throws PlcException, IOException {
		if(code == null)
		{
			c.emitRet(); // empty function code
			return;
		}


		// ------------------------------------------
		// traverse tree to allocate automatic vars?
		// ------------------------------------------
		int n_auto_vars = svars.getUsedSlots();
		int n_int_auto_vars = isvars.getUsedSlots();
		// ------------------------------------------

		// ------------------------------------------
		// generate prologue code here
		// ------------------------------------------

		// check number of args
		int n_args = args_def.size();
		String good_args_label = c.getLabel();

		c.emitIConst_32bit(n_args);
		c.emitISubLU();
		c.emitJz(good_args_label);

		// wrong count - throw string
		// BUG! Need less consuming way of reporting this. Maybe by
		// calling class object Method? Or by summoning something?
		c.emitString("arg count: "+name + " in " + s.get_class().getName());
		c.emitThrow();

		c.markLabel(good_args_label);

		if(requestDebug) c.emitDebug((byte)0x1,"Enabled debug");

		// push nulls to reserve stack space for autovars
		// BUG! We can execute vars initialization code here, can we?
		// We can if code does not depend on auto vars itself, or depends only on
		// previous ones.
		// TODO: BUG! autovars in arguments are already on stack, we don't have to reserve space
		for( int i = n_auto_vars; i > 0; i-- )
			c.emitPushNull();

		// TODO introduce instruction to reserve o+i space in one step
		// Reserve integer stack place for int vars
		for( int i = n_int_auto_vars; i > 0; i-- )
			c.emitIConst_0();

		// ------------------------------------------


		// ------------------------------------------
		// generate main code by descending the tree
		// ------------------------------------------
		code.generate_code( c, s );
		// ------------------------------------------

		// ------------------------------------------
		// generate epilogue code here
		// ------------------------------------------
		if(requestDebug) c.emitDebug((byte)0x2,"Disabled debug");
		c.emitRet(); // catch the fall-out
		// ------------------------------------------

	}


	// ------------------------------------------
	// LLVM codegen support
	// ------------------------------------------

	private static int llvmTempNum = 0;

	public String getLlvmTempName(String nodeName ) 
	{
		if( null == nodeName )
			return String.format("%%tmp_%d", llvmTempNum++ );
		return String.format("%%tmp_%d_%s", llvmTempNum++, nodeName ); 
	}



	public void generateLlvmCode( CodeGeneratorState s, BufferedWriter llvmFile ) throws PlcException, IOException {
		
		LlvmCodegen llc = new LlvmCodegen(s.get_class(),this,llvmFile);
		
		StringBuilder argdef = new StringBuilder();

		boolean firstParm = true;
		for( ArgDefinition a : args_def )
		{
			if(!firstParm)
				argdef.append(", ");

			firstParm= false;

			argdef.append("i64 %"+a.getName());
		}

		String llvmMethodName = name;
		name = name.replaceAll("<init>", "_\\$_Constructor");
		
		llc.putln(String.format("define %s @%s(%s) {", llc.getObjectType(), name, argdef )); // function 

		if(code != null)
		{

			// ------------------------------------------
			// traverse tree to allocate automatic vars?
			// ------------------------------------------
			//int n_auto_vars = svars.getUsedSlots();
			//int n_int_auto_vars = isvars.getUsedSlots();
			// ------------------------------------------

			// ------------------------------------------
			// generate prologue code here
			// ------------------------------------------

			/*
		// check number of args
		int n_args = args_def.size();
		String good_args_label = c.getLabel();

		c.emitIConst_32bit(n_args);
		c.emitISubLU();
		c.emitJz(good_args_label);

		// wrong count - throw string
		// BUG! Need less consuming way of reporting this. Maybe by
		// calling class object Method? Or by summoning something?
		c.emitString("arg count: "+name + " in " + s.get_class().getName());
		c.emitThrow();

		c.markLabel(good_args_label);
			 */

			if(requestDebug) llc.emitDebug((byte) 0x1);
			//if(requestDebug) llc.emitDebug((byte)0x1,"Enabled debug");

			// push nulls to reserve stack space for autovars
			// BUG! We can execute vars initialization code here, can we?
			// We can if code does not depend on auto vars itself, or depends only on
			// previous ones.
			// 		for( int i = n_auto_vars; i > 0; i-- ) 			c.emitPushNull();

			// Reserve integer stack place for int vars 		for( int i = n_int_auto_vars; i > 0; i-- )			c.emitIConst_0();

			// ------------------------------------------


			// ------------------------------------------
			// generate main code by descending the tree
			// ------------------------------------------
			code.generateLlvmCode( llc );
			// ------------------------------------------

			// ------------------------------------------
			// generate epilogue code here
			// ------------------------------------------

			//if(requestDebug) c.emitDebug((byte)0x2,"Disabled debug");
			if(requestDebug) llc.emitDebug((byte) 0x2);

		}
		
		// catch the fall-out
		llc.putln("ret "+llc.getObjectType()+" <{ i8* null, i8* null }> ;"); // empty function code
		llc.putln("}"); // end of function 

		// ------------------------------------------
		// Part of code is generated to the buffer to 
		// be emitted after the method code. Flush it
		// now.
		// ------------------------------------------

		llc.flushPostponedCode();
		
	}


	// ------------------------------------------
	// Getters/setters
	// ------------------------------------------


	public int getOrdinal() {
		//if(ordinal < 0)			System.out.println("Method.getOrdinal(): ordinal < 0");
		return ordinal; 
	}

	public void setOrdinal(int ord) {
		ordinal = ord;		
	}


	public void setDebugMethod(boolean requestDebug) {
		this.requestDebug = requestDebug;
	}

	public boolean getDebugMethod() {
		return requestDebug;
	}

};












