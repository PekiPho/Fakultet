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
                name: "Rezervoar",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Sifra = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    Zapremina = table.Column<float>(type: "real", nullable: false),
                    VremePoslednjegCiscenja = table.Column<DateTime>(type: "datetime2", nullable: false),
                    FrekvencijaCiscenja = table.Column<int>(type: "int", nullable: false),
                    Kapacitet = table.Column<float>(type: "real", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Rezervoar", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "Riba",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    Masa = table.Column<float>(type: "real", nullable: false),
                    Vrsta = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    GodineStarosti = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Riba", x => x.Id);
                });

            migrationBuilder.CreateTable(
                name: "UbaciRibu",
                columns: table => new
                {
                    Id = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    DatumDodavanja = table.Column<DateTime>(type: "datetime2", nullable: false),
                    RibaId = table.Column<int>(type: "int", nullable: true),
                    RezervoarId = table.Column<int>(type: "int", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_UbaciRibu", x => x.Id);
                    table.ForeignKey(
                        name: "FK_UbaciRibu_Rezervoar_RezervoarId",
                        column: x => x.RezervoarId,
                        principalTable: "Rezervoar",
                        principalColumn: "Id");
                    table.ForeignKey(
                        name: "FK_UbaciRibu_Riba_RibaId",
                        column: x => x.RibaId,
                        principalTable: "Riba",
                        principalColumn: "Id");
                });

            migrationBuilder.CreateIndex(
                name: "IX_UbaciRibu_RezervoarId",
                table: "UbaciRibu",
                column: "RezervoarId");

            migrationBuilder.CreateIndex(
                name: "IX_UbaciRibu_RibaId",
                table: "UbaciRibu",
                column: "RibaId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "UbaciRibu");

            migrationBuilder.DropTable(
                name: "Rezervoar");

            migrationBuilder.DropTable(
                name: "Riba");
        }
    }
}
