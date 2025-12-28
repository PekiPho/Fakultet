namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    // DbSet kolekcije!

    public DbSet<Knjiga> Knjiga { get; set; }

    public DbSet<Biblioteka> Biblioteka { get; set; }

    public DbSet<Izdavanje> Izdavanje { get; set; }

    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
