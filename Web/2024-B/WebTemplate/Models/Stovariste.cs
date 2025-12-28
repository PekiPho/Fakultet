

namespace WebTemplate.Models{

    public class Stovariste{

        [Key]
        public int Id { get; set; }

        public required string Ime { get; set; }

        public required string Adresa { get; set; }

        [Length(10,10)]
        public required string BrojTelefona { get; set; }

        public List<Magacin>? Magacin { get; set; }
    }
}