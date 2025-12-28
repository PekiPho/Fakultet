namespace WebTemplate.Models;

public class Korisnik{

    [Key]
    public int Id { get; set; }

    public required string Ime { get; set; }

    public required string Prezime { get; set; }

    [Length(13,13)]
    public required string JMBG { get; set; }

    public required string Mail { get; set; }

    public required string Sifra { get; set; }

    public List<Pretplata>? Pretplate { get; set; }

}