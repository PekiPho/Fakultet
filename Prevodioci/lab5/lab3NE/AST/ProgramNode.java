package AST;

public class ProgramNode extends ASTNode{

    private Block mainBlock;

    public ProgramNode(Block b){
        this.mainBlock =b;
    }

    public void translate(BufferedWriter out) throws IOException{
        if(mainBlock!=null){
            mainBlock.translate(out);
        }
    }
}