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

    [HttpPost("DodajRezervoar")]
    public async Task<ActionResult> DodajRezervoar([FromBody] Rezervoar r){

        await Context.Rezervoar.AddAsync(r);
        await Context.SaveChangesAsync();

        return Ok($"Uspesno dodat rezervoar sa ID: {r.Id}");
    }

    [HttpPost("DodajRibu")]
    public async Task<ActionResult> DodajRibu([FromBody] Riba riba){

        await Context.Riba.AddAsync(riba);
        await Context.SaveChangesAsync();

        return Ok($"Uspesno dodata riba sa ID: {riba.Id}");
    }

    [HttpPost("DodajRibuURezervoar/{idRezervoara}/{idRibe}")]
    public async Task<ActionResult> DodajRibuURezervoar(int idRezervoara,int idRibe){
        
        var rez = await Context.Rezervoar.FindAsync(idRezervoara);
        var riba=await Context.Riba.FindAsync(idRibe);

        if(rez==null)
            return BadRequest($"Rezervoar sa ID: {idRezervoara} ne postoji");

        if(riba==null)
            return BadRequest($"Riba sa ID: {idRibe} ne postoji");

        var postoji=await Context.UbaciRibu.Include(x=>x.Rezervoar)
                                        .Include(x=>x.Riba)
                                        .Where(x=>x.Rezervoar!.Id == idRezervoara && (riba.Masa<x.Riba!.Masa/10 || riba.Masa>x.Riba!.Masa*10))
                                        .FirstOrDefaultAsync();
        if(postoji!=null)
            return BadRequest("Postoji riba koja bi pojela nasu ribu, ili riba koju bi nasa riba pojela");

        rez.Kapacitet-=riba.Masa;

        if(rez.Kapacitet< 0)
            return BadRequest("Rezervoar je pun");
        
        if(rez.BrojJedinki==null)
            rez.BrojJedinki = new Dictionary<string, int>();
        
        if(!rez.BrojJedinki.ContainsKey(riba.Vrsta))
            rez.BrojJedinki[riba.Vrsta]=0;

        
        rez.BrojJedinki[riba.Vrsta]++;
        

        var ubaci = new UbaciRibu{
            Riba=riba,
            Rezervoar=rez,
            DatumDodavanja=DateTime.Now
        };

        Context.Rezervoar.Update(rez);
        await Context.UbaciRibu.AddAsync(ubaci);
        await Context.SaveChangesAsync();

        return Ok($"Riba sa ID-em: {idRibe} uspesno dodata u rezervoar sa ID: {idRezervoara}");

    }

    [HttpPut("PromeniRibu/{idRezervoara}/{idRibe}")]
    public async Task<ActionResult> PromeniRibu(int idRezervoara,int idRibe){
        
        var zapromenu=await Context.UbaciRibu.Include(x=>x.Rezervoar)
                                                .Include(x=>x.Riba)
                                                .Where(x=> x.Rezervoar!.Id==idRezervoara && x.Riba!.Id==idRibe)
                                                .FirstOrDefaultAsync();
        
        if(zapromenu==null)
            return BadRequest($"Riba sa ID-em: {idRibe} ne postoji u rezervoaru: {idRezervoara}");

        zapromenu.DatumDodavanja=DateTime.Now; // ne razumem sta se trazi da se promeni ??

        Context.Update(zapromenu);
        await Context.SaveChangesAsync();

        return Ok("Jedinka uspesno promenjena");

    }

    [HttpGet("RezervoarZaCiscenje")]
    public async Task<ActionResult> RezervoariZaCiscenje(){

        var r=await Context.Rezervoar.Where(x=>x.VremePoslednjegCiscenja.AddDays(x.FrekvencijaCiscenja) < DateTime.Now)
                            .Select(x=>x.Sifra)
                            .ToListAsync(); //verovatno ne treba ovako ali ne znam na koji nacin da prikazem sve
        
        string naziv="";
        foreach(string a in r){
           naziv+= a + "\n";
        }

        return Ok($"{naziv}");
    }

    [HttpGet("UkupnaMasaURezervoaru/{idRezervoara}")]
    public async Task<ActionResult> UkupnaMasaURezervoaru(int idRezervoara){

        var suma = await Context.UbaciRibu.Include(x=>x.Rezervoar)
                                            .Include(x=>x.Riba)
                                            .Where(x=>x.Rezervoar!.Id == idRezervoara)
                                            .Select(x=>x.Riba!.Masa)
                                            .SumAsync();

        return Ok($"Ukupna suma u rezervoaru sa ID: {idRezervoara} je: {suma}");
    }
    

    // [HttpGet("VratiJedinke/{idRezervoara}")]
    // public async Task<ActionResult> VratiJedinke(int idRezervoara){

    //     var rez=await Context.Rezervoar.FindAsync(idRezervoara);

    //     if(rez==null)
    //         return BadRequest("Rezervoar ne postoji");

        
    //     if(rez.BrojJedinki==null)
    //         return BadRequest("Greska");

    //     string rezS="";
    //     foreach(var item in rez.BrojJedinki){

    //         rezS+=item.Key + ":  " + item.Value.ToString() + "\n";
    //         // rezS.Concat(item.Key);
    //         // rezS.Concat(":  ");
    //         // rezS.Concat(item.Value.ToString());
    //         // rezS.Concat("\n");
    //     }

    //     return Ok(rezS);
    // }
}
