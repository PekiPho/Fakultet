
namespace WebTemplate.Models{

    public class Materijal{

        [Key]
        public int Id { get; set; }

        public int? Sifra { get; set; }

        public required string Naziv { get; set; }

        public double? Cena { get; set; }

        public required string NazivProizvodjaca { get; set; }

        public List<Magacin>? Magacin { get; set; }
    }
}