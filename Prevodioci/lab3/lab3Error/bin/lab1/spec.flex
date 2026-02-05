package lab1;
import java_cup.runtime.*;

%%

// sekcija opcija i deklaracija
%class MPLexer
%cup
%line
%column
%debug


%eofval{
return new Symbol(sym.EOF);
%eofval}

%{
KWTable kwTable = new KWTable();

    private Symbol symbol(int type) {
        return new Symbol(type, yyline, yycolumn);
    }
    
    private Symbol symbol(int type, Object value) {
        return new Symbol(type, yyline, yycolumn, value);
    }
	
	public int getLine() {
        return yyline + 1;
    }
%}

// stanja
%xstate KOMENTAR

// makroi
slovo      = [a-zA-Z_]
cifra      = [0-9]
hexcifra   = [0-9a-fA-F]
octcifra   = [0-7]

%%

//pravila
"%%"           { yybegin(KOMENTAR); }
<KOMENTAR>"%%" { yybegin(YYINITIAL); }
<KOMENTAR>.|\n {  }


[\t\r\n ]+ { ; }

// separatori
"(" { return symbol(sym.LPAREN); }
")" { return symbol(sym.RPAREN); }
"{" { return symbol(sym.LBRACE); }
"}" { return symbol(sym.RBRACE); }
"," { return symbol(sym.COMMA); }
";" { return symbol(sym.SEMICOLON); }
":" { return symbol(sym.COLON); }

// operatori
"+" { return symbol(sym.PLUS); }
"-" { return symbol(sym.MINUS); }
"=" { return symbol(sym.ASSIGN); }

//kljucne reci
{slovo}({slovo}|{cifra})* { 
    int tokenType = kwTable.find(yytext());
    return symbol(tokenType, yytext()); 
}

//konstante
{cifra}+"."{cifra}*([eE][+-]?{cifra}+)? { return symbol(sym.CONST, yytext()); }
"0oct"{octcifra}+ |
"0hex"{hexcifra}+ |
"0dec"{cifra}+ |
{cifra}+ { return symbol(sym.CONST, yytext()); }
\'[^\']\' { return symbol(sym.CONST, yytext()); }

. {
    System.out.println("LEXICAL ERROR: " + yytext()
        + " at line " + (yyline+1) + ", column " + (yycolumn+1));
}