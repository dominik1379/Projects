package sk.tuke.kpi.kp.bejeweled.service;

import sk.tuke.kpi.kp.bejeweled.entity.Rating;

import java.sql.*;
import java.time.LocalDate;

public class RatingServiceJDBC implements RatingService {
    private static final String URL = "jdbc:postgresql://localhost:5432/postgres";
    private static final String USER = "postgres";
    private static final String PASSWORD = "admin";

    private static final String INSERT_OR_UPDATE =
            "INSERT INTO rating (player, game, rating, rated_on) VALUES (?, ?, ?, ?) " +
                    "ON CONFLICT (player, game) DO UPDATE " +
                    "SET rating = EXCLUDED.rating, rated_on = EXCLUDED.rated_on";

    private static final String SELECT_USER_RATING =
            "SELECT rating FROM rating WHERE game = ? AND player = ?";

    private static final String DELETE = "DELETE FROM rating";

    private static final String SELECT_AVG_RATING =
            "SELECT AVG(rating) FROM rating WHERE game = ?";

    @Override
    public void setRating(Rating rating) {
        if (rating.getRating() < 1 || rating.getRating() > 5) {
            throw new RatingException("Rating must be between 1 and 5!");
        }

        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(INSERT_OR_UPDATE)) {

            statement.setString(1, rating.getPlayer());
            statement.setString(2, rating.getGame());
            statement.setInt(3, rating.getRating());
            statement.setDate(4, Date.valueOf(rating.getRatedOn()));

            statement.executeUpdate();
        } catch (SQLException e) {
            throw new RatingException("Problem inserting or updating rating", e);
        }
    }

    @Override
    public int getAverageRating(String game) {
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(SELECT_AVG_RATING)) {

            statement.setString(1, game);
            try (ResultSet rs = statement.executeQuery()) {
                return rs.next() ? (int) Math.round(rs.getDouble(1)) : 0;
            }

        } catch (SQLException e) {
            throw new RatingException("Problem retrieving average rating", e);
        }
    }

    @Override
    public int getRating(String game, String player) {
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement statement = connection.prepareStatement(SELECT_USER_RATING)) {

            statement.setString(1, game);
            statement.setString(2, player);
            try (ResultSet rs = statement.executeQuery()) {
                return rs.next() ? rs.getInt(1) : 0;
            }
        } catch (SQLException e) {
            throw new RatingException("Problem retrieving player rating", e);
        }
    }

    @Override
    public void reset() {
        try (Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
             Statement statement = connection.createStatement()) {

            statement.executeUpdate(DELETE);
        } catch (SQLException e) {
            throw new RatingException("Problem deleting ratings", e);
        }
    }
}
