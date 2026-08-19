package sk.tuke.kpi.kp.bejeweled.core;

import sk.tuke.kpi.kp.bejeweled.entity.Score;

import java.time.LocalDate;
import java.util.Date;

public class ScoringSystem {
    private int score;
    private String gameName;
    private String playerName;

    public ScoringSystem(String gameName, String playerName) {
        this.score = 0;
        this.gameName = gameName;
        this.playerName = playerName;
    }

    //Za kazdy odstraneny gem prida 10 bodov
    public void addPoints(int gemsCleared) {
        score += gemsCleared * 10;
    }

    public int getScore() {
        return score;
    }

    public String getPlayerName() {
        return playerName;
    }


    public Score createScoreRecord() {
        return new Score(gameName, playerName, score, LocalDate.now());
    }

    @Override
    public String toString() {
        return "Score: " + score;
    }
}
