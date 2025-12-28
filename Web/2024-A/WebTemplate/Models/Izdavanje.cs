

namespace WebTemplate.Models
{

    public class Izdavanje
    {
        [Key]
        public int Id { get; set; }

        public DateTime VremeIzdavanja { get; set; }

        public DateTime VremeVracanja { get; set; }

        public Biblioteka? Biblioteka { get; set; }

        public Knjiga? Knjiga { get; set; }

    }
}
