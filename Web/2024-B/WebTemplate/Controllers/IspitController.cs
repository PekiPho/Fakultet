namespace WebTemplate.Controllers;

[ApiController]
[Route("[controller]")]
public class IspitController : ControllerBase
{
    public IspitContext Context { get; set; }

    public IspitController(IspitContext context)
    {
        Context = context;
    }

    [HttpPost("DodajStovariste")]
    public async Task<ActionResult> DodajStovariste([FromBody]Stovariste s){

        if(s==null)
            return BadRequest("Podaci nisu uneseni");
        
        await Context.Stovariste.AddAsync(s);
        await Context.SaveChangesAsync();

        return Ok($"Uspesno dodato stovariste sa id: {s.Id}");
    }

    [HttpPost("DodajMaterijal")]
    public async Task<ActionResult> DodajMaterijal([FromBody]Materijal m){

        if(m==null)
            return BadRequest("Podaci nisu uneseni");

        await Context.Materijal.AddAsync(m);
        await Context.SaveChangesAsync();

        return Ok($"Uspesno dodat materijal sa id: {m.Id}");
    }


    [HttpPost("DodajUMagacin/{idMaterijala}/{idStovarista}/{kolicina}")]
    public async Task<ActionResult> DodajUMagacin(int idMaterijala,int idStovarista,int kolicina){

        var materijal = await Context.Materijal.FindAsync(idMaterijala);
        var stovariste = await Context.Stovariste.FindAsync(idStovarista);

        if(materijal==null)
            return BadRequest("Materijal ne postoji");
        
        if(stovariste==null)
            return BadRequest("Stovariste ne postoji");

        var magacin= new Magacin(){
            Materijal=materijal,
            Stovariste=stovariste,
            Kolicina=kolicina,
            DatumDostave=DateTime.Now
        };

        await Context.Magacin.AddAsync(magacin);
        await Context.SaveChangesAsync();

        return Ok($"Uspesno dodat materijal. ID: {magacin.Id}");
    }

    [HttpGet("UkupnaKolicinaMaterijala/{idStovarista}")]
    public async Task<ActionResult> UkupnaKolicinaMaterijala(int idStovarista){

        var suma=await Context.Magacin.Include(x=>x.Stovariste)
                                .Include(x=>x.Materijal)
                                .Where(x=>x.Stovariste!.Id == idStovarista)
                                .SumAsync(x=>x.Kolicina);

        return Ok($"Ukupna kolicina materijala je: {suma}");
    }

    [HttpPut("ProdajMaterijal/{idStovarista}/{idMaterijala}/{kolicina}")]
    public async Task<ActionResult> ProdajMaterijal(int idStovarista,int idMaterijala,int kolicina){

        var a= await Context.Magacin.Include(x=>x.Stovariste)
                                .Include(x=>x.Materijal)
                                .Where(x=> x.Stovariste!.Id == idStovarista && x.Materijal!.Id == idMaterijala && x.Kolicina >=kolicina)
                                .OrderBy(x=>x.DatumDostave)
                                .FirstOrDefaultAsync();
        if(a==null)
            return BadRequest("Ne postoji materijal sa trazenom kolicinom");
        
        a.Kolicina-=kolicina;
        Context.Magacin.Update(a);
        await Context.SaveChangesAsync();

        return Ok($"Uspesna prodaja materijala ID: {a.Id}");
    }

    [HttpGet("NajviseMaterijala/{idStovarista}")]
    public async Task<ActionResult> NajviseMaterijala(int idStovarista){

        var a=await Context.Magacin.Include(x=>x.Stovariste)
                        .Include(x=>x.Materijal)
                        .Where(x=> x.Stovariste!.Id == idStovarista)
                        .GroupBy(x=>x.Materijal.Id)
                        //.OrderByDescending(y=>y.Sum(x=>x.Kolicina))
                        // .GroupBy(x=>x.Materijal!.Id)
                        .Select(y=> new{
                            Materijal= y.Key,
                            Suma= y.Sum(x=>x.Kolicina)
                        })
                        .OrderByDescending(x=> x.Suma).FirstOrDefaultAsync();
        
        return Ok($"Najvise ima {a!.Materijal} , kolicina je {a.Suma}");
    }
}
