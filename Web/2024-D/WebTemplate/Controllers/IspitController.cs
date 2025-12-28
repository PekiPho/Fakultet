using Microsoft.VisualBasic;

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

    [HttpPost("DodajKorisnika")]
    public async Task<ActionResult> DodajKorisnika([FromBody] Korisnik k){

        await Context.Korisnik.AddAsync(k);
        await Context.SaveChangesAsync();

        return Ok($"Uspesno dodat korisnik sa ID: {k.Id}");
    }

    [HttpPost("DodajAplikaciju")]
    public async Task<ActionResult> DodajAplikaciju([FromBody]Aplikacija a){

        await Context.Aplikacija.AddAsync(a);
        await Context.SaveChangesAsync();

        return Ok($"Uspesno dodata aplikacija sa ID: {a.Id}");
    }

    [HttpPost("DodajPretplatu/{idKorisnika}/{idAplikacije},{kljucPretplate}/{brojMeseci}")]
    public async Task<ActionResult> DodajPretplatu(int idKorisnika,int idAplikacije,string kljucPretplate,int brojMeseci){

        var k= await Context.Korisnik.FindAsync(idKorisnika);
        var a= await Context.Aplikacija.FindAsync(idAplikacije);

        if(k==null)
            return BadRequest("Korisnik sa zadatim ID-em ne postoji");

        if(a==null)
            return BadRequest("Aplikacija sa zadatim ID-em ne postoji");
        
        if(kljucPretplate.Length != 15)
            return BadRequest("Kljuc pretplate mora da ima 15 karaktera");

        var p=new Pretplata{
            Aplikacija=a,
            Korisnik=k,
            KljucPretplate=kljucPretplate,
            BrojMeseciPretplate=brojMeseci,
            DatumPocetka=DateTime.Now,
            DatumIsteka=DateTime.Now.AddMonths(brojMeseci)
        };

        await Context.Pretplata.AddAsync(p);
        await Context.SaveChangesAsync();


        return Ok($"Uspesno dodata pretplata sa ID: {p.Id}");
    }

    [HttpPut("ObnoviPretplatu/{idKorisnika}/{idAplikacije}/{kljucPretplate}/{brojMeseci}")]
    public async Task<ActionResult> ObnoviPretplatu(int idKorisnika,int idAplikacije,string kljucPretplate,int brojMeseci){

        var p=await Context.Pretplata.Include(x=> x.Aplikacija)
                                .Include(x=>x.Korisnik)
                                .Where(x=> x.Aplikacija!.Id== idAplikacije && x.Korisnik!.Id == idKorisnika && x.KljucPretplate== kljucPretplate)
                                .FirstOrDefaultAsync();

        if(p==null)
            return BadRequest("Pretplata ne postoji");

        p.DatumPocetka=DateTime.Now;
        p.DatumIsteka=DateTime.Now.AddMonths(brojMeseci);
        p.BrojMeseciPretplate=brojMeseci;

        Context.Pretplata.Update(p);
        await Context.SaveChangesAsync();

        return Ok($"Uspesno obnovljena pretplata sa ID: {p.Id}");
    }

    [HttpGet("KolikoKorisnikaIsteklo")]
    public async Task<ActionResult> KolikoKorisnikaIsteklo(){

        var sum=await Context.Pretplata.Include(x=>x.Korisnik)
                                        .Where(x=> x.DatumIsteka < DateTime.Now)
                                        .CountAsync();

        return Ok($"Ukupan broj korisnika kojima je istekla pretplata je: {sum}");
        
    }

    [HttpGet("UkupnaZarada")]
    public async Task<ActionResult> UkupnaZarada(){

        var suma=await Context.Pretplata.Include(x=>x.Aplikacija)
                                        .SumAsync(x=>x.BrojMeseciPretplate*x.Aplikacija!.CenaPretplate);

        return Ok($"Ukupna zarada je: {suma}");
    }
    
}
