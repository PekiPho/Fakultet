package AST;

public class Subtract extends BinaryExpression{
    public Subtract(Expression left,Expression right){
        super(left,right);
    }

    protected String opCode(){
        return "Sub";
    }
}