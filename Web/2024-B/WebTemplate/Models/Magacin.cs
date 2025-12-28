


namespace WebTemplate.Models{

    public class Magacin{

        [Key]
        public int Id { get; set; }

        public int Kolicina { get; set; }

        public DateTime DatumDostave { get; set; }

        public Stovariste? Stovariste { get; set; }

        public Materijal? Materijal { get; set; }
    }
}