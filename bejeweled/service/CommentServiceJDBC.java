package sk.tuke.kpi.kp.bejeweled.service;

import sk.tuke.kpi.kp.bejeweled.entity.Comment;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class CommentServiceJDBC implements CommentService {
    private static final String URL = "jdbc:postgresql://localhost:5432/postgres";
    private static final String USER = "postgres";
    private static final String PASSWORD = "admin";

    private static final String INSERT =
            "INSERT INTO comment (game, player, comment, commented_on) VALUES (?, ?, ?, ?)";
    private static final String SELECT =
            "SELECT game, player, comment, commented_on FROM comment WHERE game = ? ORDER BY commented_on DESC";
    private static final String DELETE = "DELETE FROM comment";

    @Override
    public void addComment(Comment comment) {
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(INSERT)) {

            statement.setString(1, comment.getGame());
            statement.setString(2, comment.getPlayer());
            statement.setString(3, comment.getComment());
            statement.setDate(4, java.sql.Date.valueOf(comment.getCommentedOn()));

            statement.executeUpdate();
        } catch (SQLException e) {
            throw new CommentException("Problem inserting comment", e);
        }
    }

    @Override
    public List<Comment> getComments(String game) {
        List<Comment> comments = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(SELECT)) {

            statement.setString(1, game);
            try (ResultSet rs = statement.executeQuery()) {
                while (rs.next()) {
                    comments.add(new Comment(
                            rs.getString("game"),
                            rs.getString("player"),
                            rs.getString("comment"),
                            rs.getDate("commented_on").toLocalDate()
                    ));
                }
            }
        } catch (SQLException e) {
            throw new CommentException("Problem retrieving comments", e);
        }
        return comments;
    }

    @Override
    public void reset() {
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             Statement statement = connection.createStatement()) {
            statement.executeUpdate(DELETE);
        } catch (SQLException e) {
            throw new CommentException("Problem deleting comments", e);
        }
    }
}
