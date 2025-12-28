namespace WebTemplate.Models;

public class IspitContext : DbContext
{
    // DbSet kolekcije!
    public DbSet<Aplikacija> Aplikacija { get; set; }

    public DbSet<Korisnik> Korisnik { get; set; }

    public DbSet<Pretplata> Pretplata { get; set; }

    public IspitContext(DbContextOptions options) : base(options)
    {
        
    }
}
