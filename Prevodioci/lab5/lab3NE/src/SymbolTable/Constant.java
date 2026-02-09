package SymbolTable;

public class Constant {
	public Type type;
	public Object value;
	public Constant( Type constType, Object constValue )
	{
		type = constType;
		value = constValue;
	}

	public Constant(Object constValue){
		type=null;
		value=constValue;
	}
}
