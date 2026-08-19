package sk.tuke.kpi.kp.bejeweled.service;

import org.springframework.web.client.RestTemplate;
import sk.tuke.kpi.kp.bejeweled.entity.Comment;

import java.util.Arrays;
import java.util.List;

public class CommentServiceRestClient implements CommentService {
    private final String url = "http://localhost:8080/api/comment";
    private final RestTemplate restTemplate;

    public CommentServiceRestClient(RestTemplate restTemplate) {
        this.restTemplate = restTemplate;
    }

    @Override
    public void addComment(Comment comment) {
        restTemplate.postForEntity(url, comment, Comment.class);
    }

    @Override
    public List<Comment> getComments(String game) {
        return Arrays.asList(
                restTemplate.getForEntity(url + "/" + game, Comment[].class).getBody()
        );
    }

    @Override
    public void reset() {
        throw new UnsupportedOperationException("Reset not supported via REST client.");
    }
}
