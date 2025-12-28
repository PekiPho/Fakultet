using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebTemplate.Migrations
{
    /// <inheritdoc />
    public partial class v1 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Biblioteka",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Ime = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Adresa = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Email = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    MyProperty = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Biblioteka", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Knjiga",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Naslov = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Autor = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    NazivIzdavaca = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    GodinaIzdavanja = table.Column<long>(type: "bigint", nullable: false),
                    BrojUEvidenciji = table.Column<long>(type: "bigint", nullable: false),
                    BibliotekaId = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Knjiga", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Knjiga_Biblioteka_BibliotekaId",
                        column: x => x.BibliotekaId,
                        principalTable: "Biblioteka",
                        principalColumn: "Id");
                });

            migrationBuilder.CreateTable(
                name: "Izdavanje",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Name = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    VremeIzdavanja = table.Column<DateTime>(type: "datetime2", nullable: false),
                    VremeVracanja = table.Column<DateTime>(type: "datetime2", nullable: false),
                    BibliotekaId = table.Column<int>(type: "int", nullable: true),
                    KnjigaId = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Izdavanje", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Izdavanje_Biblioteka_BibliotekaId",
                        column: x => x.BibliotekaId,
                        principalTable: "Biblioteka",
                        principalColumn: "Id");
                    table.ForeignKey(
                        name: "FK_Izdavanje_Knjiga_KnjigaId",
                        column: x => x.KnjigaId,
                        principalTable: "Knjiga",
                        principalColumn: "Id");
                });

            migrationBuilder.CreateIndex(
                name: "IX_Izdavanje_BibliotekaId",
                table: "Izdavanje",
                column: "BibliotekaId");

            migrationBuilder.CreateIndex(
                name: "IX_Izdavanje_KnjigaId",
                table: "Izdavanje",
                column: "KnjigaId");

            migrationBuilder.CreateIndex(
                name: "IX_Knjiga_BibliotekaId",
                table: "Knjiga",
                column: "BibliotekaId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Izdavanje");

            migrationBuilder.DropTable(
                name: "Knjiga");

            migrationBuilder.DropTable(
                name: "Biblioteka");
        }
    }
}
