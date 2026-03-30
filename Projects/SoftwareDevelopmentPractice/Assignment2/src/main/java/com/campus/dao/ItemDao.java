package com.campus.dao;

import com.campus.entity.Item;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

@Repository
public class ItemDao {
    private static final List<Item> items = new ArrayList<>();
    private static final AtomicInteger idGenerator = new AtomicInteger(1);

    static {
        // Mock data
        items.add(new Item(idGenerator.getAndIncrement(), "二手耳机", "音质超棒", 150.0, "电子产品", "wx123", "张三", new Date(), "出售中"));
        items.add(new Item(idGenerator.getAndIncrement(), "Java核心技术", "全新未拆封", 50.0, "书籍", "wx456", "李四", new Date(), "出售中"));
        items.add(new Item(idGenerator.getAndIncrement(), "篮球", "七成新", 30.0, "生活用品", "wx789", "张三", new Date(), "出售中"));
    }

    public List<Item> findAll() {
        return new ArrayList<>(items);
    }

    public Item findById(Integer id) {
        return items.stream().filter(item -> item.getId().equals(id)).findFirst().orElse(null);
    }

    public void save(Item item) {
        if (item.getId() == null) {
            item.setId(idGenerator.getAndIncrement());
            items.add(item);
        } else {
            // Update
            for (int i = 0; i < items.size(); i++) {
                if (items.get(i).getId().equals(item.getId())) {
                    items.set(i, item);
                    return;
                }
            }
        }
    }

    public List<Item> findBySellerName(String sellerName) {
        return items.stream().filter(item -> item.getSellerName().equals(sellerName)).collect(Collectors.toList());
    }

    public void delete(Integer id) {
        items.removeIf(item -> item.getId().equals(id));
    }

    public List<Item> findByCategory(String category) {
        return items.stream().filter(item -> item.getCategory().equals(category)).collect(Collectors.toList());
    }
}
