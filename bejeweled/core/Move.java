package sk.tuke.kpi.kp.bejeweled.core;

public class Move {
    private final Field field;
    private final int row1, col1, row2, col2;

    public Move(Field field, int row1, int col1, int row2, int col2) {
        this.field = field;
        this.row1 = row1;
        this.col1 = col1;
        this.row2 = row2;
        this.col2 = col2;
    }

    // Metoda na vykonanie pohybu ak je platny
    public boolean execute() {
        if (swappable()) {
            field.swapTiles(row1, col1, row2, col2);
            return true;
        }
        return false;
    }

    // Vola metodu swappable pre aktualne ulozene suradnice pohybu v objekte Move
    public boolean swappable() {
        return swappable(row1, col1, row2, col2);
    }

    // Metoda kontroluje ci sa daju gemy vymenit aby vzniklo spojenie
    public boolean swappable(int row1, int col1, int row2, int col2) {
        if (!field.isValidPosition(row1, col1) || !field.isValidPosition(row2, col2)) {
            return false;
        }

        if (!areAdjacent(row1, col1, row2, col2)) {
            return false;
        }

        field.swapTiles(row1, col1, row2, col2);
        boolean matchExists = field.isMatch(row1, col1) || field.isMatch(row2, col2);
        field.swapTiles(row1, col1, row2, col2);

        return matchExists;
    }

    // Metoda overuje ci su gemy susedne vertikalne alebo horizontalne
    public boolean areAdjacent(int row1, int col1, int row2, int col2) {
        return (Math.abs(row1 - row2) == 1 && col1 == col2) ||
                (Math.abs(col1 - col2) == 1 && row1 == row2);
    }
}
