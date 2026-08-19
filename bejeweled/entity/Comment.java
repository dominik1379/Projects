package sk.tuke.kpi.kp.bejeweled.entity;

import com.fasterxml.jackson.annotation.JsonFormat;

import javax.persistence.*;
import java.time.LocalDate;

@Entity
@NamedQueries({
        @NamedQuery(name = "Comment.getComments",
                query = "SELECT c FROM Comment c WHERE c.game = :game ORDER BY c.commentedOn DESC"),
        @NamedQuery(name = "Comment.resetComments",
                query = "DELETE FROM Comment")
})
public class Comment {
    private String game;
    private String player;
    private String comment;

    @JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "yyyy-MM-dd")
    private LocalDate commentedOn;

    @Id
    @GeneratedValue
    private int ident;

    public Comment(String game, String player, String comment, LocalDate commentedOn) {
        this.game = game;
        this.player = player;
        this.comment = comment;
        this.commentedOn = commentedOn;
    }

    public Comment() {}

    public String getGame() { return game; }
    public void setGame(String game) { this.game = game; }

    public String getPlayer() { return player; }
    public void setPlayer(String player) { this.player = player; }

    public String getComment() { return comment; }
    public void setComment(String comment) { this.comment = comment; }

    public LocalDate getCommentedOn() { return commentedOn; }
    public void setCommentedOn(LocalDate commentedOn) { this.commentedOn = commentedOn; }

    public int getIdent() { return ident; }
    public void setIdent(int ident) { this.ident = ident; }

    @Override
    public String toString() {
        return "Comment{" +
                "game='" + game + '\'' +
                ", player='" + player + '\'' +
                ", comment='" + comment + '\'' +
                ", commentedOn=" + commentedOn +
                '}';
    }
}
