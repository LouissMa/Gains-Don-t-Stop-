package com.petstore.dao;

import com.petstore.model.PetProfile;
import com.petstore.util.DBUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class PetProfileDAO {
    public boolean addPet(PetProfile pet) {
        String sql = "INSERT INTO `pet_profiles` (`user_id`, `name`, `type`, `breed`, `age`) VALUES (?, ?, ?, ?, ?)";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, pet.getUserId());
            stmt.setString(2, pet.getName());
            stmt.setString(3, pet.getType());
            stmt.setString(4, pet.getBreed());
            stmt.setInt(5, pet.getAge());
            return stmt.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public List<PetProfile> getPetsByUserId(int userId) {
        List<PetProfile> list = new ArrayList<>();
        String sql = "SELECT * FROM `pet_profiles` WHERE `user_id` = ? ORDER BY `create_time` DESC";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, userId);
            try (ResultSet rs = stmt.executeQuery()) {
                while (rs.next()) {
                    PetProfile p = new PetProfile();
                    p.setId(rs.getInt("id"));
                    p.setUserId(rs.getInt("user_id"));
                    p.setName(rs.getString("name"));
                    p.setType(rs.getString("type"));
                    p.setBreed(rs.getString("breed"));
                    p.setAge(rs.getInt("age"));
                    p.setCreateTime(rs.getTimestamp("create_time"));
                    list.add(p);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    public boolean deletePet(int petId) {
        String sql = "DELETE FROM `pet_profiles` WHERE `id` = ?";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, petId);
            return stmt.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public int countByTypeKeyword(String keyword) {
        String sql = "SELECT COUNT(*) AS c FROM `pet_profiles` WHERE `type` LIKE ?";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, "%" + keyword + "%");
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt("c");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }
}
