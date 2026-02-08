package AST;

import java.io.*;
import SymbolTable.Constant;


public class WhenStatement extends ASTNode{
    private Constant constant;
    private Statement statement;

    public WhenStatement(Constant c,Statement s){
        this.constant=c;
        this.statement=s;
    }

    public Constant getConstant(){
        return constant;
    }

    public Statement getStatement(){
        return statement;
    }

    public void translate(BufferedWriter out) throws IOException{

        if(statement!=null){
            statement.translate(out);
        }
    }
}