package sk.tuke.kpi.kp.bejeweled.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.time.LocalDate;

@Entity
@Table(name = "users")
@NamedQueries({
        @NamedQuery(
                name = "User.findByLogin",
                query = "SELECT u FROM User u WHERE u.login = :login"
        ),
        @NamedQuery(
                name = "User.checkExists",
                query = "SELECT COUNT(u) FROM User u WHERE u.login = :login"
        ),
        @NamedQuery(
                name = "User.resetUsers",
                query = "DELETE FROM User"
        )
})
public class User implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int ident;

    @Column(unique = true, nullable = false)
    private String login;

    @Column(nullable = false)
    private String password;

    private LocalDate lastLogin;

    public User() {
    }

    public User(String login, String password) {
        this.login = login;
        this.password = password;
        this.lastLogin = LocalDate.now();
    }

    public int getIdent() {
        return ident;
    }

    public void setIdent(int ident) {
        this.ident = ident;
    }

    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public LocalDate getLastLogin() {
        return lastLogin;
    }

    public void setLastLogin(LocalDate lastLogin) {
        this.lastLogin = lastLogin;
    }

    @Override
    public String toString() {
        return "User{" +
                "login='" + login + '\'' +
                ", lastLogin=" + lastLogin +
                '}';
    }
}
