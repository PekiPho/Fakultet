import java.util.Hashtable;

public class KWTable {

    private Hashtable mTable;

    public KWTable() {
        // Inicijalizacija hash tabele koja pamti kljucne reci
        mTable = new Hashtable();

        // Dodajemo kljucne reci vaseg jezika
        mTable.put("main", new Integer(sym.MAIN));
        mTable.put("int", new Integer(sym.INT));
        mTable.put("char", new Integer(sym.CHAR));
        mTable.put("float", new Integer(sym.FLOAT));
        mTable.put("case", new Integer(sym.CASE));
        mTable.put("when", new Integer(sym.WHEN));
    }

    /**
     * Vraca ID kljucne reci 
     */
    public int find(String keyword) {
        Object symbol = mTable.get(keyword);
        if (symbol != null)
            return ((Integer)symbol).intValue();

        // Ako rec nije pronadjena u tabeli kljucnih reci radi se o identifikatoru
        return sym.ID;
    }
}
