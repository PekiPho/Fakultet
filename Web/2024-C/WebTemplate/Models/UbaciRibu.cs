namespace WebTemplate.Models;


public class UbaciRibu{

    public int Id { get; set; }

    public DateTime DatumDodavanja { get; set; }

    public static Dictionary<string,int>? BrojJedinki { get; set; }

    public Riba? Riba { get; set; }

    public Rezervoar? Rezervoar { get; set; }
}