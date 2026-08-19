package sk.tuke.kpi.kp.bejeweled.service;

import org.springframework.stereotype.Component;
import org.springframework.transaction.annotation.Transactional;
import sk.tuke.kpi.kp.bejeweled.entity.User;

import javax.persistence.EntityManager;
import javax.persistence.NoResultException;
import javax.persistence.PersistenceContext;
import javax.persistence.TypedQuery;
import java.time.LocalDate;
import java.util.List;

@Component
@Transactional
public class UserServiceJPA implements UserService {

    @PersistenceContext
    private EntityManager entityManager;

    @Override
    public User login(String login, String password) {
        if (login == null || password == null) {
            return null;
        }

        try {
            TypedQuery<User> query = entityManager.createNamedQuery("User.findByLogin", User.class);
            query.setParameter("login", login);
            List<User> users = query.getResultList();

            if (users.isEmpty()) {
                return null;
            }

            User user = users.get(0);
            if (user.getPassword().equals(password)) {
                user.setLastLogin(LocalDate.now());
                return user;
            }
        } catch (Exception e) {
            System.err.println("Error during login: " + e.getMessage());
        }

        return null;
    }

    @Override
    public boolean register(User user) {
        if (user == null || user.getLogin() == null || user.getPassword() == null) {
            return false;
        }

        try {
            if (userExists(user.getLogin())) {
                return false;
            }

            user.setLastLogin(LocalDate.now());
            entityManager.persist(user);
            return true;
        } catch (Exception e) {
            System.err.println("Failed to register user: " + e.getMessage());
            return false;
        }
    }

    @Override
    public boolean userExists(String login) {
        try {
            TypedQuery<Long> query = entityManager.createNamedQuery("User.checkExists", Long.class);
            query.setParameter("login", login);
            Long count = query.getSingleResult();
            return count > 0;
        } catch (Exception e) {
            System.err.println("Failed to check if user exists: " + e.getMessage());
            return false;
        }
    }

    @Override
    public boolean changePassword(User user, String newPassword) {
        try {
            if (user == null) {
                return false;
            }

            TypedQuery<User> query = entityManager.createNamedQuery("User.findByLogin", User.class);
            query.setParameter("login", user.getLogin());
            List<User> users = query.getResultList();

            if (users.isEmpty()) {
                return false;
            }

            User existingUser = users.get(0);
            if (existingUser.getPassword().equals(user.getPassword())) {
                existingUser.setPassword(newPassword);
                entityManager.merge(existingUser);
                return true;
            }
            return false;
        } catch (Exception e) {
            System.err.println("Failed to change password: " + e.getMessage());
            return false;
        }
    }

    @Override
    public void reset() {
        entityManager.createNamedQuery("User.resetUsers").executeUpdate();
    }
}