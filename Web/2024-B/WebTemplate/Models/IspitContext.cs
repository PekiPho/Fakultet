namespace WebTemplate.Models
{
    public class IspitContext : DbContext
    {
        // DbSet kolekcije!
        public required DbSet<Materijal> Materijal { get; set; }

        public required DbSet<Magacin> Magacin { get; set; }

        public required DbSet<Stovariste> Stovariste { get; set; }
        public IspitContext(DbContextOptions options) : base(options)
        {

        }
    }
}


