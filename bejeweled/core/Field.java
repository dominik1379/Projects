package sk.tuke.kpi.kp.bejeweled.core;

import sk.tuke.kpi.kp.bejeweled.core.enums.GameState;

public class Field {
    private final int rowCount;
    private final int columnCount;
    private final Tile[][] tiles;
    private GameState gameState;

    // Inicializuje hracie pole a vygeneruje ho
    public Field(int rowCount, int columnCount) {
        this.rowCount = rowCount;
        this.columnCount = columnCount;
        this.tiles = new Tile[rowCount][columnCount];
        this.gameState = GameState.PLAYING;
        generate();
    }

    // Metoda na vygenerovanie pola, kde na zaciatku bude aspon 1 mozne spojenie
    private void generate() {
        do {
            for (int row = 0; row < rowCount; row++) {
                for (int col = 0; col < columnCount; col++) {
                    Gem newGem;
                    do {
                        newGem = Gem.randomGem();
                        tiles[row][col] = new Tile(newGem, row, col);
                    } while (isMatch(row, col));
                }
            }
        } while (!hasPossibleMoves());
    }

    // Metoda na vymenu 2 drahokamov
    public void swapTiles(int row1, int col1, int row2, int col2) {
        Tile temp = tiles[row1][col1];
        tiles[row1][col1] = tiles[row2][col2];
        tiles[row2][col2] = temp;

        tiles[row1][col1].setPosition(row1, col1);
        tiles[row2][col2].setPosition(row2, col2);
    }

    // Metoda odstrani vsetky spojenia, aplikuje gravitaciu a prida body do skore
    public void clearAndDrop(ScoringSystem scoringSystem) {
        boolean removed;

        do {
            removed = false;
            boolean[][] toRemove = new boolean[rowCount][columnCount];
            int removedGems = 0;

            for (int row = 0; row < rowCount; row++) {
                for (int col = 0; col < columnCount; col++) {
                    if (isMatch(row, col)) {
                        markMatches(row, col, toRemove);
                        removed = true;
                    }
                }
            }

            if (removed) {
                for (int row = 0; row < rowCount; row++) {
                    for (int col = 0; col < columnCount; col++) {
                        if (toRemove[row][col]) {
                            tiles[row][col] = null;
                            removedGems++;
                        }
                    }
                }

                scoringSystem.addPoints(removedGems);
                gravity();
            }
        } while (removed);

        checkGameState();
    }

    // Metoda presuve gemy zhora nadol ak je pod nimi prazdne miesto a vyplni vrsok novymi
    private void gravity() {
        for (int col = 0; col < columnCount; col++) {
            int emptyRow = rowCount - 1;

            for (int row = rowCount - 1; row >= 0; row--) {
                if (tiles[row][col] != null) {
                    tiles[emptyRow][col] = tiles[row][col];
                    tiles[emptyRow][col].setPosition(emptyRow, col);
                    emptyRow--;
                }
            }

            for (int row = emptyRow; row >= 0; row--) {
                tiles[row][col] = new Tile(Gem.randomGem(), row, col);
            }
        }
    }

    //Metoda oznaci vsetky spojenia
    private void markMatches(int row, int col, boolean[][] toRemove) {
        String color = tiles[row][col].getGem().getImagePath();

        int left = countMatches(row, col, 0, -1, color);
        int right = countMatches(row, col, 0, 1, color);
        if (left + right >= 2) {
            for (int i = -left; i <= right; i++) {
                toRemove[row][col + i] = true;
            }
        }

        int up = countMatches(row, col, -1, 0, color);
        int down = countMatches(row, col, 1, 0, color);
        if (up + down >= 2) {
            for (int i = -up; i <= down; i++) {
                toRemove[row + i][col] = true;
            }
        }
    }

    // Metoda kontroluje ci zadane suradnice nie su von z herneho pola
    public boolean isValidPosition(int row, int col) {
        if (row < 0 || row >= rowCount) {
            return false;
        }
        if (col < 0 || col >= columnCount) {
            return false;
        }
        return true;
    }

    // Metoda pocita pocet spojenych gemov
    private int countMatches(int row, int col, int rowDir, int colDir, String color) {
        int count = 0;
        int next_r = row + rowDir;
        int next_c = col + colDir;

        while (isValidPosition(next_r, next_c) && tiles[next_r][next_c] != null && tiles[next_r][next_c].getGem().getImagePath().equals(color)) {
            count++;
            next_r += rowDir;
            next_c += colDir;
        }
        return count;
    }

    // Metoda kontroluje ci na danej pozici je spojenie
    public boolean isMatch(int row, int col) {
        String color = tiles[row][col].getGem().getImagePath();

        int verticalMatches = countMatches(row, col, -1, 0, color) + countMatches(row, col, 1, 0, color);
        int horizontalMatches = countMatches(row, col, 0, -1, color) + countMatches(row, col, 0, 1, color);

        if (verticalMatches >= 2) {
            return true;
        }
        if (horizontalMatches >= 2) {
            return true;
        }

        return false;
    }

    // Metoda meni stav hry podla toho ci je este nejake mozne spojenie
    private void checkGameState() {
        if (!hasPossibleMoves()) {
            gameState = GameState.NO_POSSIBLE_MOVES;
        }
    }

    // Metoda zistuje ci je aspon 1 mozne spojenie v poli
    public boolean hasPossibleMoves() {
        for (int row = 0; row < rowCount; row++) {
            for (int col = 0; col < columnCount; col++) {
                Move move1 = new Move(this, row, col, row + 1, col);
                Move move2 = new Move(this, row, col, row, col + 1);

                if (move1.swappable() || move2.swappable()) {
                    return true;
                }
            }
        }
        return false;
    }

    public Tile[][] getTiles() {
        return tiles;
    }

    public Tile getTile(int row, int col) {
        return tiles[row][col];
    }

    public int getRowCount() {
        return rowCount;
    }

    public int getColumnCount() {
        return columnCount;
    }

    public GameState getGameState() {
        return gameState;
    }


}
