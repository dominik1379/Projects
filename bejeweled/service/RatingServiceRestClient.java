package sk.tuke.kpi.kp.bejeweled.service;

import org.springframework.web.client.RestTemplate;
import sk.tuke.kpi.kp.bejeweled.entity.Rating;

public class RatingServiceRestClient implements RatingService {
    private final String url = "http://localhost:8080/api/rating";
    private final RestTemplate restTemplate;

    public RatingServiceRestClient(RestTemplate restTemplate) {
        this.restTemplate = restTemplate;
    }

    @Override
    public void setRating(Rating rating) {
        restTemplate.postForEntity(url, rating, Rating.class);
    }

    @Override
    public int getAverageRating(String game) {
        return restTemplate.getForObject(url + "/" + game + "/average", Integer.class);
    }

    @Override
    public int getRating(String game, String player) {
        return restTemplate.getForObject(url + "/" + game + "/" + player, Integer.class);
    }

    @Override
    public void reset() {
        throw new UnsupportedOperationException("Reset not supported via REST client.");
    }
}
