namespace WebTemplate.Models;


public class Riba{

    [Key]
    public int Id { get; set; }

    public float Masa { get; set; }

    public required string Vrsta { get; set; }

    public int GodineStarosti { get; set; }

    public List<UbaciRibu>? UbaciRibu { get; set; }
}