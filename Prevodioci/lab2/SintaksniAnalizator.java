import java.io.IOException;
import java.util.*;
public class SintaksniAnalizator
{
	HashMap<String,Integer> mapaVrste = new HashMap<>();
	HashMap<String,Integer> mapaKolone = new HashMap<>();
	
	String[][] sintaksnaTabela = new String[13][10];
	String[] smene = new String[5];
	public SintaksniAnalizator()
	{
		mapaVrste.put("RE", 0);
		mapaVrste.put("RE'", 1);
		mapaVrste.put("A", 2);
		mapaVrste.put("read", 3);
		mapaVrste.put("(", 4);
		mapaVrste.put("ID", 5);
		mapaVrste.put("in", 6);
		mapaVrste.put(")", 7);
		mapaVrste.put("do", 8);
		mapaVrste.put(";", 9);
		mapaVrste.put("=", 10);
		mapaVrste.put("CONST", 11);
		mapaVrste.put("#", 12);
		
		mapaKolone.put("read", 0);
		mapaKolone.put("(", 1);
		mapaKolone.put("ID", 2);
		mapaKolone.put("in", 3);
		mapaKolone.put(")", 4);
		mapaKolone.put("do", 5);
		mapaKolone.put(";", 6);
		mapaKolone.put("=", 7);
		mapaKolone.put("CONST", 8);
		mapaKolone.put("#", 9);
		
		
		smene[0] = "read ( ID in ID ) do RE";
		smene[1] = "A RE'";
		smene[2] = "; A RE'";
		smene[3] = "";
		smene[4] = "ID = CONST";
		for(int i=0; i<12; i++)
		{
			for(int j=0; j<10; j++)
			{
				sintaksnaTabela[i][j] = "";
			}
		}
		for(int i=3; i<12;i++)
		{
			sintaksnaTabela[i][i-3] = "pop";
		}
		sintaksnaTabela[12][9] = "acc";
		
		sintaksnaTabela[0][0] = "0";
		sintaksnaTabela[0][2] = "1";
		sintaksnaTabela[1][6] = "2";
		sintaksnaTabela[1][9] = "3";
		sintaksnaTabela[2][2] = "4";
		
		for(int i=0; i<12; i++)
		{
			for(int j=0; j<10; j++)
			{
				if(sintaksnaTabela[i][j] == "")
					sintaksnaTabela[i][j] = "err";
			}
		}
		
		
		
	}
	public void reverse(String a[])
	{
		String[] b = new String[a.length];
        int j = a.length;
        for (int i = 0; i < a.length; i++) {
            b[j - 1] = a[i];
            j = j - 1;
        }
        a = b;
		
	}
	public String M(String top, Yytoken next)
	{
		String[] ss = top.split(" ");
		if(next.m_index == 11)
		{
			if(ss[0].equals("ID"))
			{
				return "pop";
			}
			return sintaksnaTabela[mapaVrste.get(top)][mapaKolone.get("ID")];
		}
		if(next.m_index == 12)
		{
			if(ss[0].equals("CONST"))
				return "pop";
			else
				return sintaksnaTabela[mapaVrste.get(top)][mapaKolone.get("CONST")];
		}
		if(ss[0].equals("#") && next.m_text.equals("#"))
		{
			return "acc";
		}
		if(ss[0].equals(next.m_text))
		{
			return "pop";
		}
		if(mapaKolone.containsKey(next.m_text))
		return sintaksnaTabela[mapaVrste.get(top)][mapaKolone.get(next.m_text)];
		
		return "err";
	}
	public boolean SA_LL1(MPLexer lexer)
	{
		Stack<String> stek = new Stack<>();
		stek.push("#");
		stek.push("RE");
		boolean prepoznat = false;
		boolean greska = false;
		String s;
		String[] niz;
		try {
			 Yytoken next = lexer.next_token();
			do
			{
				s = M(stek.peek(), next);
				switch(s)
				{
				case "pop":
					stek.pop();
					next = lexer.next_token();
					break;
				case "acc":
					prepoznat = true;
					break;
				case "err":
					greska = true;
					break;
				default:
					stek.pop();
					niz = smene[Integer.parseInt(s)].split(" ");
					String[] b = new String[niz.length];
			        int j = niz.length;
			        for (int i = 0; i < niz.length; i++) {
			            b[j - 1] = niz[i];
			            j = j - 1;
			        }
					for(String str : b)
					{
						if(!str.equals(""))
						stek.push(str);
					}
					break;
				}
				
				
				
			}while(!(prepoznat || greska));
			
			return prepoznat;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return prepoznat;
		
	}
}
