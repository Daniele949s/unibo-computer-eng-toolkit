//Achille Pisani 0001070863

public class Elemento {
    private String id;
    private String patente;
    private String tipo;
    private String img;

    // Costruttore
    public Elemento() {
        this.targa = "L";
        this.patente = "L";
        this.tipo = "L";
        this.img = "L";
    }

    // Getter e Setter
    public String getTarga() {
        return targa;
    }

    public void setTarga(String targa) {
        this.targa = targa;
    }

    public String getPatente() {
        return patente;
    }

    public void setPatente(String patente) {
        this.patente = patente;
    }

    public String getTipo() {
        return tipo;
    }

    public void setTipo(String tipo) {
        this.tipo = tipo;
    }

    public String getImg() {
        return img;
    }

    public void setImg(String img) {
        this.img = img;
    }
}
