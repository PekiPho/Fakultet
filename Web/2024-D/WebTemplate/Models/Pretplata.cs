namespace WebTemplate.Models;


public class Pretplata{

    [Key]
    public int Id { get; set; }

    [Length(15,15)]
    public required string KljucPretplate { get; set; }

    public int BrojMeseciPretplate { get; set; }

    public DateTime DatumPocetka { get; set; }

    public DateTime DatumIsteka { get; set; }

    public Aplikacija? Aplikacija { get; set; }

    public Korisnik? Korisnik { get; set; }
}