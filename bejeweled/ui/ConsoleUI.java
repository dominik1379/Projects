package sk.tuke.kpi.kp.bejeweled.ui;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import sk.tuke.kpi.kp.bejeweled.core.*;
import sk.tuke.kpi.kp.bejeweled.core.enums.GameState;
import sk.tuke.kpi.kp.bejeweled.entity.Comment;
import sk.tuke.kpi.kp.bejeweled.entity.Rating;
import sk.tuke.kpi.kp.bejeweled.entity.Score;
import sk.tuke.kpi.kp.bejeweled.service.CommentService;
import sk.tuke.kpi.kp.bejeweled.service.RatingService;
import sk.tuke.kpi.kp.bejeweled.service.ScoreService;

import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

@Component
public class ConsoleUI {
    private Field field;
    private Timer timer;
    private ScoringSystem scoringSystem;
    private final Scanner scanner = new Scanner(System.in);
    private boolean isRunning;

    @Autowired
    private ScoreService scoreService;

    @Autowired
    private RatingService ratingService;

    @Autowired
    private CommentService commentService;

    private String playerName;
    private int rows;
    private int cols;

    public void configure(int rows, int cols, String playerName) {
        this.rows = rows;
        this.cols = cols;
        this.playerName = playerName;
        this.field = new Field(rows, cols);
        this.timer = new Timer();
        this.scoringSystem = new ScoringSystem("Bejeweled", playerName);
        this.isRunning = true;
    }

    public void play() {
        timer.start();
        System.out.println("\n\tWelcome to game Bejeweled!");

        while (isRunning) {
            printField();
            printScore();
            handleInput();

            if (field.getGameState() == GameState.NO_POSSIBLE_MOVES) {
                printField();
                System.out.println("\nNo more possible moves! Game Over!");
                isRunning = false;
            }

            if (field.getGameState() == GameState.GAME_OVER) {
                isRunning = false;
            }
        }

        endGame();
    }


    //Metoda na vykreslenie herneho pola
    private void printField() {
        int rows = field.getRowCount();
        int cols = field.getColumnCount();

        System.out.print("\n    ");
        for (int col = 1; col <= cols; col++) {
            System.out.printf("%- 3d", col);
        }
        System.out.println("\n   " + "-".repeat(cols * 3 + 2));

        for (int row = 0; row < rows; row++) {
            System.out.printf("%2d | ", row + 1);
            for (int col = 0; col < cols; col++) {
                System.out.print(field.getTile(row, col) + "  ");
            }
            System.out.println("|");
        }
        System.out.println("  " + "-".repeat(cols * 3 + 2));
    }

    //Metoda na vypis aktualneho skore a casu
    private void printScore() {
        int totalSeconds = timer.getTime();
        String formattedTime = formatTime(totalSeconds);
        System.out.println("Score: " + scoringSystem.getScore() + " | Time: " + formattedTime);
    }

    //Metoda na ziskanie a kontrolu uzivatelskeho inputu pocas hry
    private void handleInput() {
        System.out.print("\nEnter 4 numbers to move (row1 col1 row2 col2) or 'exit' to end game: ");
        String input = scanner.nextLine().trim();

        if (input.equalsIgnoreCase("exit")) {
            isRunning = false;
            return;
        }

        String[] parts = input.split(" ");

        if (parts.length != 4) {
            System.out.println("Invalid input! Enter exactly four numbers.");
            return;
        }

        int row1, col1, row2, col2;

        try {
            row1 = Integer.parseInt(parts[0]) - 1;
            col1 = Integer.parseInt(parts[1]) - 1;
            row2 = Integer.parseInt(parts[2]) - 1;
            col2 = Integer.parseInt(parts[3]) - 1;
        } catch (NumberFormatException e) {
            System.out.println("Invalid input! Enter only numbers.");
            return;
        }

        if (isValidMove(row1, col1, row2, col2)) {
            Move move = new Move(field, row1, col1, row2, col2);
            if (move.execute()) {
                System.out.println("Move executed!");
                field.clearAndDrop(scoringSystem);
            } else {
                System.out.println("Invalid move! Try again.");
            }
        } else {
            System.out.println("Move is out of bounds! Try again.");
        }
    }

    //Metoda kontroluje ci sme nevysli z herneho pola pri zadani suradnic
    private boolean isValidMove(int row1, int col1, int row2, int col2) {
        if (row1 < 0 || row1 >= field.getRowCount()){
            return false;
        }
        else if (col1 < 0 || col1 >= field.getColumnCount()){
            return false;
        }
        else if (row2 < 0 || row2 >= field.getRowCount()){
            return false;
        }
        else if (col2 < 0 || col2 >= field.getColumnCount()){
            return false;
        }
        else {
            return true;
        }
    }

    //Metoda ktora zabezpeci interakciu s hracom po ukonceni hry
    private void endGame() {
        timer.stop();
        int finalPoints = scoringSystem.getScore();
        String player = scoringSystem.getPlayerName();

        Score finalScore = new Score("Bejeweled", player, finalPoints, LocalDate.now());
        scoreService.addScore(finalScore);

        System.out.println("\nGame Over!");
        System.out.println("Final Score: " + finalScore.getPoints() +
                " | Player: " + finalScore.getPlayer() +
                " | Time: " + formatTime(timer.getTime()));

        while (true) {
            System.out.println("\nWhat would you like to do?");
            System.out.println("1 - Rate the game");
            System.out.println("2 - Add a comment");
            System.out.println("3 - Show top 10 players");
            System.out.println("4 - Show all comments");
            System.out.println("5 - Show average rating");
            System.out.println("6 - Exit");
            System.out.print("Enter your choice: ");

            String choice = scanner.nextLine().trim();
            switch (choice) {
                case "1":
                    int rating = askForRating();
                    Rating finalRating = new Rating("Bejeweled", player, rating, LocalDate.now());
                    ratingService.setRating(finalRating);
                    System.out.println("Your rating has been saved.");
                    break;
                case "2":
                    askForComment(player);
                    break;
                case "3":
                    showTopScores();
                    break;
                case "4":
                    showAllComments();
                    break;
                case "5":
                    showAverageRating();
                    break;
                case "6":
                    System.out.println("Thanks for playing!");
                    return;
                default:
                    System.out.println("Invalid choice! Try again.");
            }
        }

    }

    // Metoda pre ziskanie hodnotenia od hraca
    private int askForRating() {
        int rating = 0;
        while (true) {
            System.out.print("Please rate the game (1-5): ");
            String input = scanner.nextLine().trim();
            try {
                rating = Integer.parseInt(input);
                if (rating >= 1 && rating <= 5) {
                    break;
                } else {
                    System.out.println("Invalid rating! Please enter a number between 1 and 5.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid input! Please enter a valid whole number (1-5).");
            }
        }
        return rating;
    }
    //Metoda pre pisanie komentarov
    private void askForComment(String player) {
        System.out.print("Enter your comment: ");
        String commentText = scanner.nextLine().trim();
        if (!commentText.isEmpty()) {
            Comment comment = new Comment("Bejeweled", player, commentText,LocalDate.now());
            commentService.addComment(comment);
            System.out.println("Your comment has been saved.");
        } else {
            System.out.println("No comment entered.");
        }
    }
    //Metoda pre vypis top10 hracov
    private void showTopScores() {
        List<Score> topScores = scoreService.getTopScores("Bejeweled");
        System.out.println("\nTop 10 Players:");
        for (Score score : topScores) {
            System.out.println(score.getPlayer() + " - " + score.getPoints() + " points");
        }
    }
    //Metoda pre vypis vsetkych komentov
    private void showAllComments() {
        List<Comment> comments = commentService.getComments("Bejeweled");

        if (comments.isEmpty()) {
            System.out.println("\nNo comments found for this game.");
        } else {
            System.out.println("\nAll Comments:");
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
            for (Comment comment : comments) {
                System.out.println(comment.getPlayer() + ": " + comment.getComment() +
                        " (Commented on: " + comment.getCommentedOn().format(formatter) + ")");
            }
        }
    }
    //Metoda pre priemer hodnoteni
    private void showAverageRating() {
        int averageRating = ratingService.getAverageRating("Bejeweled");
        System.out.println("\nAverage Rating: " + averageRating + " stars");
    }

    //Metoda pre formatovany casovac
    private String formatTime(int totalSeconds) {
        int hours = totalSeconds / 3600;
        int minutes = (totalSeconds % 3600) / 60;
        int seconds = totalSeconds % 60;
        return String.format("%02d:%02d:%02d", hours, minutes, seconds);
    }
}
