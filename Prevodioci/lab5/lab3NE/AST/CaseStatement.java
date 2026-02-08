package AST;

import java.io.*;
import java.util.ArrayList;


public class CaseStatement extends Statement{
    private Expression condition;
    private ArrayList whenStatements;

    public CaseStatement(Expression e,ArrayList list){
        this.condition=e;
        this.whenStatements=list;
    }

    public void translate(BufferedWriter out) throws IOException{

        String endLabel=ASTNode.genLab();

        for(int i=0;i<whenStatements.size();i++){
            WhenStatement currentWhen= (WhenStatement) whenStatements.get(i);
            String nextBranchLabel = ASTNode.genLab();

            condition.translate(out);
            condition.genLoad("R1",out);

            ConstantExpression constExpr = new ConstantExpression(currentWhen.getConstant());
            constExpr.translate(out);
            constExpr.genLoad("R2",out);

            out.write("\tCompare_Equal\tR1, R2");
            out.newLine();

            out.write("\tJumpIfZero\tR1, " + nextBranchLabel);
            out.newLine();

            currentWhen.translate(out);
            out.write("\tJump\t\t" + endLabel);
            out.newLine();

            out.write(nextBranchLabel + ":");
            out.newLine();
        }

        out.write(endLabel + ":");
        out.newLine();
    }
}