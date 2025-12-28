using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebTemplate.Migrations
{
    /// <inheritdoc />
    public partial class v3 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Materijal",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Sifra = table.Column<int>(type: "int", nullable: true),
                    Naziv = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Cena = table.Column<double>(type: "float", nullable: true),
                    NazivProizvodjaca = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Materijal", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Stovariste",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Ime = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Adresa = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    BrojTelefona = table.Column<string>(type: "nvarchar(max)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Stovariste", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Magacin",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Kolicina = table.Column<int>(type: "int", nullable: false),
                    DatumDostave = table.Column<DateTime>(type: "datetime2", nullable: false),
                    StovaristeId = table.Column<int>(type: "int", nullable: true),
                    MaterijalId = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Magacin", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Magacin_Materijal_MaterijalId",
                        column: x => x.MaterijalId,
                        principalTable: "Materijal",
                        principalColumn: "Id");
                    table.ForeignKey(
                        name: "FK_Magacin_Stovariste_StovaristeId",
                        column: x => x.StovaristeId,
                        principalTable: "Stovariste",
                        principalColumn: "Id");
                });

            migrationBuilder.CreateIndex(
                name: "IX_Magacin_MaterijalId",
                table: "Magacin",
                column: "MaterijalId");

            migrationBuilder.CreateIndex(
                name: "IX_Magacin_StovaristeId",
                table: "Magacin",
                column: "StovaristeId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Magacin");

            migrationBuilder.DropTable(
                name: "Materijal");

            migrationBuilder.DropTable(
                name: "Stovariste");
        }
    }
}
