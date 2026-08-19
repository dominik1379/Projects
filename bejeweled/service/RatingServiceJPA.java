package sk.tuke.kpi.kp.bejeweled.service;

import org.springframework.stereotype.Service;
import sk.tuke.kpi.kp.bejeweled.entity.Rating;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.transaction.Transactional;
import java.util.List;

@Service
@Transactional
public class RatingServiceJPA implements RatingService {

    @PersistenceContext
    private EntityManager entityManager;

    @Override
    public void setRating(Rating rating) {
        if (rating.getRating() < 1 || rating.getRating() > 5) {
            throw new RatingException("Rating must be between 1 and 5!");
        }
        Rating existing = entityManager.createQuery(
                        "SELECT r FROM Rating r WHERE r.game = :game AND r.player = :player", Rating.class)
                .setParameter("game", rating.getGame())
                .setParameter("player", rating.getPlayer())
                .getResultStream()
                .findFirst()
                .orElse(null);

        if (existing == null) {
            entityManager.persist(rating);
        } else {
            existing.setRating(rating.getRating());
            existing.setRatedOn(rating.getRatedOn());
            entityManager.merge(existing);
        }
    }

    @Override
    public int getAverageRating(String game) {
        Double avg = entityManager.createNamedQuery("Rating.getAverageRating", Double.class)
                .setParameter("game", game)
                .getSingleResult();
        return avg == null ? 0 : (int) Math.round(avg);
    }

    @Override
    public int getRating(String game, String player) {
        Integer rating = entityManager.createNamedQuery("Rating.getUserRating", Integer.class)
                .setParameter("game", game)
                .setParameter("player", player)
                .getResultStream()
                .findFirst()
                .orElse(0);
        return rating;
    }

    @Override
    public void reset() {
        entityManager.createNamedQuery("Rating.resetRatings").executeUpdate();
    }
}
