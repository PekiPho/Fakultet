%%

// sekcija opcija i deklaracija
%class MPLexer
%function next_token
%line
%column
%debug
%type Yytoken

%eofval{
    return new Yytoken(sym.EOF, null, yyline, yycolumn);
%eofval}

%{
// dodatni clanovi generisane klase
KWTable kwTable = new KWTable();

Yytoken getKW() {
    return new Yytoken(
        kwTable.find(yytext()),
        yytext(),
        yyline,
        yycolumn
    );
}
%}



// makroi
slovo      = [a-zA-Z_]
cifra      = [0-9]

%%
// whitespace
[\t\r\n ]+ { ; }

// separatori / simboli
"(" { return new Yytoken(sym.LPAREN, yytext(), yyline, yycolumn); }
")" { return new Yytoken(sym.RPAREN, yytext(), yyline, yycolumn); }
"{" { return new Yytoken(sym.LBRACE, yytext(), yyline, yycolumn); }
"}" { return new Yytoken(sym.RBRACE, yytext(), yyline, yycolumn); }
":" { return new Yytoken(sym.COLON, yytext(), yyline, yycolumn); }
";" { return new Yytoken(sym.SEMI, yytext(), yyline, yycolumn); }
"=" { return new Yytoken(sym.ASSIGN, yytext(), yyline, yycolumn); }

// kljucne reci
"case" { return new Yytoken(sym.CASE, yytext(), yyline, yycolumn); }
"when" { return new Yytoken(sym.WHEN, yytext(), yyline, yycolumn); }

// identifikatori
{slovo}({slovo}|{cifra})* { 

    int code = kwTable.find(yytext());
    return new Yytoken(code, yytext(), yyline, yycolumn);
}

// konstante (brojevi)
{cifra}+ { return new Yytoken(sym.CONST, yytext(), yyline, yycolumn); }


. {
    System.out.println("LEXICAL ERROR: " + yytext()
        + " at line " + yyline + ", column " + yycolumn);
}
