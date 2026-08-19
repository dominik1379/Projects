package sk.tuke.kpi.kp.bejeweled.server.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import sk.tuke.kpi.kp.bejeweled.core.*;
import sk.tuke.kpi.kp.bejeweled.core.enums.GameState;
import sk.tuke.kpi.kp.bejeweled.entity.Comment;
import sk.tuke.kpi.kp.bejeweled.entity.Rating;
import sk.tuke.kpi.kp.bejeweled.entity.Score;
import sk.tuke.kpi.kp.bejeweled.entity.User;
import sk.tuke.kpi.kp.bejeweled.service.CommentService;
import sk.tuke.kpi.kp.bejeweled.service.RatingService;
import sk.tuke.kpi.kp.bejeweled.service.ScoreService;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Controller
public class BejeweledController {
    private Field field;
    private ScoringSystem scoringSystem;
    private Timer timer;
    private String playerName;

    @Autowired
    private ScoreService scoreService;

    @Autowired
    private CommentService commentService;

    @Autowired
    private RatingService ratingService;

    @RequestMapping("/bejeweled")
    public String showForm(
            @RequestParam(value = "playerName", required = false) String playerName,
            @RequestParam(value = "rows", required = false, defaultValue = "8") int rows,
            @RequestParam(value = "cols", required = false, defaultValue = "8") int cols,
            Model model,
            HttpSession session) {

        User loggedUser = (User) session.getAttribute("loggedUser");
        if (loggedUser != null) {
            return startGame(loggedUser.getLogin(), rows, cols, model, session);
        }
        model.addAttribute("player", playerName);
        return "index";
    }

    @RequestMapping(value = "/bejeweled", method = RequestMethod.POST)
    public String startGame(@RequestParam("playerName") String playerName,
                            @RequestParam("rows") int rows,
                            @RequestParam("cols") int cols,
                            Model model,
                            HttpSession session) {

        User loggedUser = (User) session.getAttribute("loggedUser");

        if (loggedUser != null) {
            this.playerName = loggedUser.getLogin();
        } else {
            this.playerName = playerName;
        }

        field = new Field(rows, cols);
        timer = new Timer();
        scoringSystem = new ScoringSystem("Bejeweled", this.playerName);

        timer.start();

        model.addAttribute("player", this.playerName);
        model.addAttribute("gameBoard", field.getTiles());
        model.addAttribute("score", scoringSystem.getScore());
        model.addAttribute("time", formatTime(timer.getTime()));
        model.addAttribute("rows", rows);
        model.addAttribute("cols", cols);

        if (loggedUser != null) {
            session.setAttribute("loggedUser", loggedUser);
        }

        model.addAttribute("topScores", scoreService.getTopScores("Bejeweled"));
        model.addAttribute("comments", commentService.getComments("Bejeweled"));
        model.addAttribute("averageRating", ratingService.getAverageRating("Bejeweled"));
        model.addAttribute("userRating", loggedUser != null ?
                ratingService.getRating("Bejeweled", loggedUser.getLogin()) : 0);

        return "bejeweled";
    }


    @PostMapping("/bejeweled/move")
    @ResponseBody
    public Map<String, Object> executeMove(@RequestBody MoveRequest moveRequest) {
        Map<String, Object> response = new HashMap<>();

        Move move = new Move(field,
                moveRequest.getRow1(), moveRequest.getCol1(),
                moveRequest.getRow2(), moveRequest.getCol2());

        boolean valid = move.execute();

        if (valid) {
            field.clearAndDrop(scoringSystem);
        }

        response.put("valid", valid);
        response.put("gameBoard", field.getTiles());
        response.put("score", scoringSystem.getScore());
        response.put("gameState", field.getGameState().name());

        return response;
    }


    @PostMapping("/bejeweled/endscore")
    @ResponseBody
    public Map<String, Object> saveScore(HttpSession session) {
        Map<String, Object> response = new HashMap<>();

        User loggedUser = (User) session.getAttribute("loggedUser");

        if (loggedUser != null) {
            scoreService.addScore(new Score(
                    "Bejeweled",
                    loggedUser.getLogin(),
                    scoringSystem.getScore(),
                    LocalDate.now()
            ));
            response.put("success", true);
            response.put("message", "Score saved successfully!");
        } else {
            response.put("success", false);
            response.put("message", "You must be logged in to save scores.");
        }

        response.put("scores", scoreService.getTopScores("Bejeweled"));
        return response;
    }


    @PostMapping("/bejeweled/rating")
    @ResponseBody
    public Map<String, Object> setRating(@RequestBody RatingRequest ratingRequest, HttpSession session) {
        Map<String, Object> response = new HashMap<>();

        User loggedUser = (User) session.getAttribute("loggedUser");

        if (loggedUser != null) {
            ratingService.setRating(new Rating(
                    "Bejeweled",
                    loggedUser.getLogin(),
                    ratingRequest.getRating(),
                    LocalDate.now()
            ));
            response.put("success", true);
            response.put("message", "Rating submitted successfully!");
        } else {
            response.put("success", false);
            response.put("message", "You must be logged in to rate the game.");
        }

        response.put("averageRating", ratingService.getAverageRating("Bejeweled"));
        response.put("userRating", loggedUser != null ?
                ratingService.getRating("Bejeweled", loggedUser.getLogin()) : 0);
        return response;
    }

    @PostMapping("/bejeweled/comment")
    @ResponseBody
    public Map<String, Object> addComment(@RequestBody CommentRequest commentRequest, HttpSession session) {
        Map<String, Object> response = new HashMap<>();

        User loggedUser = (User) session.getAttribute("loggedUser");

        if (loggedUser != null) {
            commentService.addComment(new Comment(
                    "Bejeweled",
                    loggedUser.getLogin(),
                    commentRequest.getComment(),
                    LocalDate.now()
            ));
            response.put("success", true);
            response.put("message", "Comment added successfully!");
        } else {
            response.put("success", false);
            response.put("message", "You must be logged in to comment.");
        }

        response.put("comments", commentService.getComments("Bejeweled"));
        return response;
    }

    @GetMapping("/bejeweled/scores")
    @ResponseBody
    public List<Score> getScores() {
        return scoreService.getTopScores("Bejeweled");
    }

    @PostMapping("/bejeweled/scores/reset")
    @ResponseBody
    public Map<String, Object> resetScores() {
        Map<String, Object> response = new HashMap<>();
        scoreService.reset();
        response.put("success", true);
        response.put("message", "All scores reset successfully");
        return response;
    }

    @GetMapping("/bejeweled/comments")
    @ResponseBody
    public List<Comment> getComments() {
        return commentService.getComments("Bejeweled");
    }


    @GetMapping("/bejeweled/rating/average")
    @ResponseBody
    public Map<String, Object> getAverageRating() {
        Map<String, Object> response = new HashMap<>();
        response.put("averageRating", ratingService.getAverageRating("Bejeweled"));
        return response;
    }


    @PostMapping("/bejeweled/endgame")
    @ResponseBody
    public Map<String, Object> endGame(HttpSession session) {
        Map<String, Object> response = new HashMap<>();

        if (timer != null) {
            timer.stop();
        }

        User loggedUser = (User) session.getAttribute("loggedUser");
        if (loggedUser != null) {
            scoreService.addScore(new Score(
                    "Bejeweled",
                    loggedUser.getLogin(),
                    scoringSystem.getScore(),
                    LocalDate.now()
            ));
        }

        response.put("success", true);
        response.put("message", "Game ended successfully");
        return response;
    }

    @GetMapping("/bejeweled/check-login")
    @ResponseBody
    public Map<String, Object> checkLoginStatus(HttpServletRequest request, HttpServletResponse response, HttpSession session) {
        Map<String, Object> result = new HashMap<>();

        User loggedUser = (User) session.getAttribute("loggedUser");

        result.put("isLoggedIn", loggedUser != null);
        result.put("sessionId", session.getId());

        if (loggedUser != null) {
            result.put("userDetails", loggedUser.toString());
            result.put("username", loggedUser.getLogin());
        } else {
            result.put("userDetails", "No user logged in");
            result.put("username", null);
        }

        return result;
    }

    @GetMapping("/bejeweled/reset-all-sessions")
    @ResponseBody
    public Map<String, Object> resetAllSessionData(HttpServletRequest request, HttpServletResponse response,
                                                   HttpSession session) {
        Map<String, Object> result = new HashMap<>();

        session.removeAttribute("loggedUser");

        session.invalidate();

        Cookie[] cookies = request.getCookies();
        if (cookies != null) {
            for (Cookie cookie : cookies) {
                cookie.setValue("");
                cookie.setPath("/");
                cookie.setMaxAge(0);
                response.addCookie(cookie);
            }
        }

        this.playerName = null;

        result.put("success", true);
        result.put("message", "Session completely reset");
        return result;
    }

    @PostMapping("/bejeweled/comments/reset")
    @ResponseBody
    public Map<String, Object> resetComments() {
        Map<String, Object> response = new HashMap<>();
        commentService.reset();
        response.put("success", true);
        response.put("message", "All comments reset successfully");
        return response;
    }

    private String formatTime(int seconds) {
        int hours = seconds / 3600;
        int minutes = (seconds % 3600) / 60;
        int secs = seconds % 60;
        return String.format("%02d:%02d:%02d", hours, minutes, secs);
    }

    @PostMapping("/bejeweled/ratings/reset")
    @ResponseBody
    public Map<String, Object> resetRatings() {
        Map<String, Object> response = new HashMap<>();
        ratingService.reset();
        response.put("success", true);
        response.put("message", "All ratings reset successfully");
        return response;
    }

    public static class MoveRequest {
        private int row1;
        private int col1;
        private int row2;
        private int col2;

        public int getRow1() { return row1; }
        public void setRow1(int row1) { this.row1 = row1; }

        public int getCol1() { return col1; }
        public void setCol1(int col1) { this.col1 = col1; }

        public int getRow2() { return row2; }
        public void setRow2(int row2) { this.row2 = row2; }

        public int getCol2() { return col2; }
        public void setCol2(int col2) { this.col2 = col2; }
    }

    public static class RatingRequest {
        private int rating;

        public int getRating() { return rating; }
        public void setRating(int rating) { this.rating = rating; }
    }

    public static class CommentRequest {
        private String comment;

        public String getComment() { return comment; }
        public void setComment(String comment) { this.comment = comment; }
    }
}