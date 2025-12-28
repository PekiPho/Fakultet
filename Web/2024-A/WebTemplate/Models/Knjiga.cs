


namespace WebTemplate.Models
{
    public class Knjiga
    {
        [Key]
        public int Id { get; set; }

        public required string Naslov { get; set; }

        public required string Autor { get; set; }

        public required string NazivIzdavaca { get; set; }

        public required uint GodinaIzdavanja { get; set; }

        public required uint BrojUEvidenciji { get; set; }

        public Biblioteka? Biblioteka { get; set; }

        public List<Izdavanje>? Izdata  { get; set; } 


    }
}
