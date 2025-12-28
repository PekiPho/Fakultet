namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    // DbSet kolekcije!
    public DbSet<Riba> Riba { get; set; }

    public DbSet<UbaciRibu> UbaciRibu { get; set; }

    public DbSet<Rezervoar> Rezervoar { get; set; }

    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
