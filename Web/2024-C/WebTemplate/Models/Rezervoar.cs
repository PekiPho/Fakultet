namespace WebTemplate.Models;


public class Rezervoar{

    [Key]
    public int Id { get; set; }

    [Length(6,6)]
    public required string Sifra { get; set; }

    public float Zapremina { get; set; }

    public DateTime VremePoslednjegCiscenja { get; set; }

    public int FrekvencijaCiscenja { get; set; }

    public float Kapacitet { get; set; }

    [NotMapped]
    public Dictionary<string,int>? BrojJedinki { get; set; }

    public List<UbaciRibu>? ubaciRibe { get; set; }
}