namespace WebTemplate.Models;

public class Aplikacija{

    [Key]
    public int Id { get; set; }

    public required string Naziv { get; set; }

    public required string ImeProizvodjaca { get; set; }

    public DateTime DatumIzdavanja { get; set; }

    public float CenaPretplate { get; set; }


    public List<Pretplata>? Pretplate { get; set; }
}