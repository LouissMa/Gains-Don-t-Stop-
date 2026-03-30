package com.campus.service;

import com.campus.dao.ItemDao;
import com.campus.entity.Item;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ItemService {

    @Autowired
    private ItemDao itemDao;

    public List<Item> findAll() {
        return itemDao.findAll();
    }

    public Item findById(Integer id) {
        return itemDao.findById(id);
    }

    public void save(Item item) {
        itemDao.save(item);
    }

    public List<Item> findBySellerName(String sellerName) {
        return itemDao.findBySellerName(sellerName);
    }

    public void delete(Integer id) {
        itemDao.delete(id);
    }

    public List<Item> findByCategory(String category) {
        return itemDao.findByCategory(category);
    }
}
