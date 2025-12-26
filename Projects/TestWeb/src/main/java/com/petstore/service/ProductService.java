package com.petstore.service;

import com.petstore.dao.PetProfileDAO;
import com.petstore.dao.ProductDAO;
import com.petstore.model.PetProfile;
import com.petstore.model.Product;
import com.petstore.model.User;

import java.util.ArrayList;
import java.util.List;

public class ProductService {
    private ProductDAO productDAO = new ProductDAO();
    private PetProfileDAO petProfileDAO = new PetProfileDAO();

    public List<Product> getAllProducts() {
        return productDAO.findAll();
    }

    public List<Product> searchProducts(String keyword) {
        return productDAO.searchByKeyword(keyword);
    }

    public List<Product> getHotProducts() {
        return productDAO.findHotProducts();
    }

    public Product getProductById(Integer id) {
        return productDAO.findById(id);
    }

    public boolean createProduct(Product product) {
        return productDAO.createProduct(product);
    }

    public boolean updateProduct(Product product) {
        return productDAO.updateProduct(product);
    }

    public boolean deleteProduct(int id) {
        return productDAO.deleteProduct(id);
    }

    public List<Product> getRecommendedProducts(User user) {
        if (user == null) {
            return getHotProducts();
        }

        List<PetProfile> pets = petProfileDAO.getPetsByUserId(user.getId());
        List<String> keywords = new ArrayList<>();
        for (PetProfile p : pets) {
            String type = p.getType();
            if (type == null) continue;
            type = type.trim().toUpperCase();
            if ("DOG".equals(type)) {
                keywords.add("狗");
                keywords.add("Dog");
                keywords.add("汪");
            } else if ("CAT".equals(type)) {
                keywords.add("猫");
                keywords.add("Cat");
                keywords.add("喵");
            } else if ("PIG".equals(type)) {
                keywords.add("猪");
                keywords.add("Pig");
            } else if ("TURTLE".equals(type)) {
                keywords.add("龟");
                keywords.add("Turtle");
            } else if ("RABBIT".equals(type)) {
                keywords.add("兔");
                keywords.add("Rabbit");
            } else if ("HAMSTER".equals(type)) {
                keywords.add("仓鼠");
                keywords.add("Hamster");
            } else if ("BIRD".equals(type)) {
                keywords.add("鸟");
                keywords.add("Bird");
                keywords.add("鹦鹉");
            } else if ("FISH".equals(type)) {
                keywords.add("鱼");
                keywords.add("Fish");
            }
        }

        if (keywords.isEmpty()) {
            return getHotProducts();
        }

        List<Product> list = productDAO.findByNameKeywords(keywords);
        if (list.isEmpty()) {
            return getHotProducts();
        }
        return list;
    }
}
