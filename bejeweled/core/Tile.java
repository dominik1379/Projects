package sk.tuke.kpi.kp.bejeweled.core;

public class Tile {
    private Gem gem;
    private int row;
    private int column;

    public Tile(Gem gem, int row, int column) {
        this.gem = gem;
        this.row = row;
        this.column = column;
    }

    public void setGem(Gem gem) {
        this.gem = gem;
    }

    public Gem getGem() {
        return gem;
    }

    public int getRow() {
        return row;
    }

    public int getColumn() {
        return column;
    }

    public void setPosition(int row, int column) {
        this.row = row;
        this.column = column;
    }

    @Override
    public String toString() {
        return gem.toString();
    }
}
