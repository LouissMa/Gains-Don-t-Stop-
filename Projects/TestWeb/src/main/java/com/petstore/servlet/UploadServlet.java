package com.petstore.servlet;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@WebServlet("/uploads/*")
public class UploadServlet extends HttpServlet {

    public static Path getUploadBaseDir() {
        return Paths.get(System.getProperty("java.io.tmpdir"), "petstore-uploads");
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String pathInfo = req.getPathInfo();
        if (pathInfo == null || pathInfo.isBlank() || "/".equals(pathInfo)) {
            resp.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        String fileName = pathInfo.startsWith("/") ? pathInfo.substring(1) : pathInfo;
        if (fileName.contains("/") || fileName.contains("\\") || fileName.contains("..")) {
            resp.sendError(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        Path base = getUploadBaseDir();
        Path file = base.resolve(fileName).normalize();
        if (!file.startsWith(base) || !Files.exists(file) || Files.isDirectory(file)) {
            resp.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        String contentType = Files.probeContentType(file);
        if (contentType == null) contentType = "application/octet-stream";
        resp.setContentType(contentType);
        resp.setHeader("Cache-Control", "public, max-age=86400");
        resp.setContentLengthLong(Files.size(file));

        try (OutputStream out = resp.getOutputStream()) {
            Files.copy(file, out);
        }
    }
}

