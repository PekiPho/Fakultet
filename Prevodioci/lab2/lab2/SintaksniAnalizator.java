package lab2;

import java.io.IOException;
import java.util.*;

public class SintaksniAnalizator {

    HashMap<String, Integer> NT = new HashMap<>();
    HashMap<Integer, Integer> T = new HashMap<>();

    int[][] table;
    String[] prod;

    public SintaksniAnalizator() {

        NT.put("CS", 0);
        NT.put("WSL", 1);
        NT.put("WSL'", 2);
        NT.put("WS", 3);
        NT.put("ST", 4);
        NT.put("RHS", 5);

        T.put(sym.CASE, 0);
        T.put(sym.WHEN, 1);
        T.put(sym.ID, 2);
        T.put(sym.CONST, 3);
        T.put(sym.LPAREN, 4);
        T.put(sym.RPAREN, 5);
        T.put(sym.LBRACE, 6);
        T.put(sym.RBRACE, 7);
        T.put(sym.COLON, 8);
        T.put(sym.ASSIGN, 9);
        T.put(sym.SEMICOLON, 10);
        T.put(sym.EOF, 11);

        prod = new String[8];
        prod[0] = "case ( ID ) { WSL }";
        prod[1] = "WS WSL'";
        prod[2] = "";
        prod[3] = "when CONST : ST";
        prod[4] = "CS";
        prod[5] = "ID = RHS ;";
        prod[6] = "ID";
        prod[7] = "CONST";


        table = new int[6][12];
        for (int i = 0; i < 6; i++)
            Arrays.fill(table[i], -1);


        table[0][T.get(sym.CASE)] = 0;

        table[1][T.get(sym.WHEN)] = 1;


        table[2][T.get(sym.WHEN)] = 1;
        table[2][T.get(sym.RBRACE)] = 2;

        table[3][T.get(sym.WHEN)] = 3;


        table[4][T.get(sym.CASE)] = 4;
        table[4][T.get(sym.ID)] = 5;

        table[5][T.get(sym.ID)] = 6;
        table[5][T.get(sym.CONST)] = 7;
    }

    public boolean parse(MPLexer lexer) {
        Stack<String> stack = new Stack<>();
        stack.push("#");
        stack.push("CS");

        try {
            Yytoken lookahead = lexer.next_token();

            while (true) {
                String top = stack.peek();

                if (top.equals("#")) {
                    return lookahead.m_index == sym.EOF;
                }

                if (!NT.containsKey(top)) {
                    if (matches(top, lookahead)) {
                        stack.pop();
                        lookahead = lexer.next_token();
                    } else {
                        return false;
                    }
                } else {
                    int row = NT.get(top);
                    int col = T.getOrDefault(lookahead.m_index, -1);

                    if (col == -1 || table[row][col] == -1)
                        return false;

                    stack.pop();
                    String rhs = prod[table[row][col]];
                    if (!rhs.isEmpty()) {
                        String[] symbols = rhs.split(" ");
                        for (int i = symbols.length - 1; i >= 0; i--)
                            stack.push(symbols[i]);
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }

    private boolean matches(String stackSym, Yytoken tok) {
        switch (stackSym) {
            case "case": return tok.m_index == sym.CASE;
            case "when": return tok.m_index == sym.WHEN;
            case "ID": return tok.m_index == sym.ID;
            case "CONST": return tok.m_index == sym.CONST;
            case "(": return tok.m_index == sym.LPAREN;
            case ")": return tok.m_index == sym.RPAREN;
            case "{": return tok.m_index == sym.LBRACE;
            case "}": return tok.m_index == sym.RBRACE;
            case ":": return tok.m_index == sym.COLON;
            case "=": return tok.m_index == sym.ASSIGN;
            case ";": return tok.m_index == sym.SEMICOLON;
            default: return false;
        }
    }
}
