package sk.tuke.kpi.kp.bejeweled.entity;

import com.fasterxml.jackson.annotation.JsonFormat;

import javax.persistence.*;
import java.time.LocalDate;

@Entity
@NamedQueries({
        @NamedQuery(name = "Rating.getAverageRating",
                query = "SELECT AVG(r.rating) FROM Rating r WHERE r.game = :game"),
        @NamedQuery(name = "Rating.getUserRating",
                query = "SELECT r.rating FROM Rating r WHERE r.game = :game AND r.player = :player"),
        @NamedQuery(name = "Rating.resetRatings",
                query = "DELETE FROM Rating")
})
public class Rating {

    private String game;
    private String player;
    private int rating;

    @JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "yyyy-MM-dd")
    private LocalDate ratedOn;

    @Id
    @GeneratedValue
    private int ident;

    public Rating(String game, String player, int rating, LocalDate ratedOn) {
        this.game = game;
        this.player = player;
        this.rating = rating;
        this.ratedOn = ratedOn;
    }

    public Rating() {}

    public String getGame() { return game; }
    public void setGame(String game) { this.game = game; }

    public String getPlayer() { return player; }
    public void setPlayer(String player) { this.player = player; }

    public int getRating() { return rating; }
    public void setRating(int rating) { this.rating = rating; }

    public LocalDate getRatedOn() { return ratedOn; }
    public void setRatedOn(LocalDate ratedOn) { this.ratedOn = ratedOn; }

    public int getIdent() { return ident; }
    public void setIdent(int ident) { this.ident = ident; }

    @Override
    public String toString() {
        return "Rating{" +
                "game='" + game + '\'' +
                ", player='" + player + '\'' +
                ", rating=" + rating +
                ", ratedOn=" + ratedOn +
                '}';
    }
}
