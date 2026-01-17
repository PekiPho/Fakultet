%%

// sekcija opcija i deklaracija
%class MPLexer
%function next_token
%line
%column
%debug
%type Yytoken

%eofval{
return new Yytoken( sym.EOF, null, yyline, yycolumn);
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
//separatori
"(" { return new Yytoken(sym.LPAREN, yytext(), yyline, yycolumn); }
")" { return new Yytoken(sym.RPAREN, yytext(), yyline, yycolumn); }
"{" { return new Yytoken(sym.LBRACE, yytext(), yyline, yycolumn); }
"}" { return new Yytoken(sym.RBRACE, yytext(), yyline, yycolumn); }
"," { return new Yytoken(sym.COMMA, yytext(), yyline, yycolumn); }
";" { return new Yytoken(sym.SEMICOLON, yytext(), yyline, yycolumn); }
":" { return new Yytoken(sym.COLON, yytext(), yyline, yycolumn); }

//operatori
"+" { return new Yytoken(sym.PLUS, yytext(), yyline, yycolumn); }
"-" { return new Yytoken(sym.MINUS, yytext(), yyline, yycolumn); }
"=" { return new Yytoken(sym.ASSIGN, yytext(), yyline, yycolumn); }

//kljucne reci
{slovo}+ { return getKW(); }
//identifikatori
{slovo}({slovo}|{cifra})* {
    return new Yytoken(sym.ID, yytext(), yyline, yycolumn);
}
//konstante
// FLOAT konstante
{cifra}+"."{cifra}*([eE][+-]?{cifra}+)? {
    return new Yytoken(sym.CONST, yytext(), yyline, yycolumn);
}

// INT konstante
"0oct"{octcifra}+ |
"0hex"{hexcifra}+ |
"0dec"{cifra}+ |
{cifra}+ {
    return new Yytoken(sym.CONST, yytext(), yyline, yycolumn);
}
\'[^\']\' {
    return new Yytoken(sym.CONST, yytext(), yyline, yycolumn);
}
. {
    System.out.println("LEXICAL ERROR: " + yytext()
        + " at line " + yyline + ", column " + yycolumn);
}