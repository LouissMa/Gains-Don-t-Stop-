package com.lab.borrow.service;

import com.lab.borrow.entity.Category;

import java.util.List;

public interface CategoryService {
    Category create(Category category);

    Category update(Category category);

    void delete(Integer categoryId);

    Category getById(Integer categoryId);

    List<Category> listAll();

    List<Category> listByParentId(Integer parentId);
}
