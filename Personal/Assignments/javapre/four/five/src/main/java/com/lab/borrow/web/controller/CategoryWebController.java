package com.lab.borrow.web.controller;

import com.lab.borrow.entity.Category;
import com.lab.borrow.service.CategoryService;
import com.lab.borrow.web.dto.CategoryForm;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.validation.Valid;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Controller
@RequestMapping("/admin/categories")
public class CategoryWebController {
    @Resource
    private CategoryService categoryService;

    @GetMapping
    public String list(HttpServletRequest request) {
        List<Category> categories = categoryService.listAll();
        request.setAttribute("categories", categories);
        request.setAttribute("categoryMap", toMap(categories));
        return "category_list";
    }

    @GetMapping("/new")
    public String newForm(HttpServletRequest request) {
        request.setAttribute("form", new CategoryForm());
        request.setAttribute("parents", categoryService.listByParentId(null));
        request.setAttribute("action", "/admin/categories");
        return "category_form";
    }

    @PostMapping
    public String create(@Valid CategoryForm form, BindingResult bindingResult, HttpServletRequest request) {
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            request.setAttribute("form", form);
            request.setAttribute("parents", categoryService.listByParentId(null));
            request.setAttribute("action", "/admin/categories");
            return "category_form";
        }

        Category category = new Category();
        category.setCategoryName(form.getCategoryName());
        category.setParentId(form.getParentId());
        category.setDescription(form.getDescription());
        categoryService.create(category);
        return "redirect:/admin/categories";
    }

    @GetMapping("/{id}/edit")
    public String editForm(@PathVariable("id") Integer id, HttpServletRequest request) {
        Category category = categoryService.getById(id);
        CategoryForm form = new CategoryForm();
        form.setCategoryId(category.getCategoryId());
        form.setCategoryName(category.getCategoryName());
        form.setParentId(category.getParentId());
        form.setDescription(category.getDescription());
        request.setAttribute("form", form);
        request.setAttribute("parents", categoryService.listByParentId(null));
        request.setAttribute("action", "/admin/categories/" + id);
        return "category_form";
    }

    @PostMapping("/{id}")
    public String update(@PathVariable("id") Integer id, @Valid CategoryForm form, BindingResult bindingResult, HttpServletRequest request) {
        if (bindingResult.hasErrors()) {
            request.setAttribute("message", bindingResult.getFieldError() == null ? "参数错误" : bindingResult.getFieldError().getDefaultMessage());
            request.setAttribute("form", form);
            request.setAttribute("parents", categoryService.listByParentId(null));
            request.setAttribute("action", "/admin/categories/" + id);
            return "category_form";
        }

        Category category = new Category();
        category.setCategoryId(id);
        category.setCategoryName(form.getCategoryName());
        category.setParentId(form.getParentId());
        category.setDescription(form.getDescription());
        categoryService.update(category);
        return "redirect:/admin/categories";
    }

    @PostMapping("/{id}/delete")
    public String delete(@PathVariable("id") Integer id) {
        categoryService.delete(id);
        return "redirect:/admin/categories";
    }

    private Map<Integer, String> toMap(List<Category> categories) {
        Map<Integer, String> map = new HashMap<>();
        for (Category c : categories) {
            map.put(c.getCategoryId(), c.getCategoryName());
        }
        return map;
    }
}
